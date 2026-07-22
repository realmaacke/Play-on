#include "processing/PlaylistManager.hpp"
#include "Content.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

// Insert into ContainerContent, if no match is found, use movies.
void PlaylistManager::insert_item(std::vector<ContainerContent> &content,
                                  ContentItem item) {
    for (ContainerContent &iter : content) {
        if (iter.content_name == item.group) {
            iter.children.emplace_back(std::move(item));
            return;
        }
    }

    // no matching group found, fall back to "unknown"
    for (ContainerContent &iter : content) {
        if (iter.content_name == "movies") {
            iter.children.emplace_back(std::move(item));
            return;
        }
    }
}

// Starting template, to ensure that "keys" is available.
std::vector<ContainerContent> PlaylistManager::content_template() {
    return std::vector<ContainerContent>{
        {"channels", "channels"},
        {"movies", "movies"},
        {"serie", "serie"},
    };
}

// group title to lower case, then regex to assign right group.
std::string PlaylistManager::categorize_group(const std::string &group_title) {
    std::string lower = group_title;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    static const std::regex series_re(R"(seri)"); // matches "series", "serie"
    static const std::regex movie_re(R"(movie)");
    static const std::regex channel_re(R"(tv|channel|live)");

    if (std::regex_search(lower, series_re))
        return "series";
    if (std::regex_search(lower, movie_re))
        return "movies";
    if (std::regex_search(lower, channel_re))
        return "channels";

    return "unknown";
}

// Regex to capture each property.
ContentItem PlaylistManager::parse_data(std::vector<std::string> lines) {
    static const std::regex name_re(R"re(tvg-name="([^"]*)")re");
    static const std::regex logo_re(R"re(tvg-logo="([^"]*)")re");
    static const std::regex group_re(R"re(group-title="([^"]*)")re");
    static const std::regex url_re(R"re((https?://[^\s"]+))re");
    // if it is a series:
    static const std::regex episode_re(R"re([Ss](\d{1,2})\s*[Ee](\d{1,2}))re");
    std::string name, logo, group_title, url;
    std::smatch match;

    for (auto &line : lines) {
        if (std::regex_search(line, match, name_re))
            name = match[1];
        if (std::regex_search(line, match, logo_re))
            logo = match[1];
        if (std::regex_search(line, match, group_re))
            group_title = match[1];
        if (std::regex_search(line, match, url_re))
            url = match[1];
    }

    std::string group = this->categorize_group(group_title);

    ContentItem returnItem;

    returnItem.name = name;
    returnItem.image = logo;
    returnItem.group = group;
    returnItem.url = url;

    // Captures season + episode
    if (group == "series") {
        std::smatch episodes_match;

        if (std::regex_search(group_title, episodes_match, episode_re)) {
            returnItem.season = std::stoi(episodes_match[1]);
            returnItem.episode = std::stoi(episodes_match[2]);
        }
    }
    return returnItem;
}

// Entry point for thread.
// Also exit point for thread.
void PlaylistManager::retrive_data() {
    std::ifstream playlist_file("./data/playlist.m3u");
    std::vector<ContainerContent> content = this->content_template();
    std::vector<std::string> temp_lines;
    std::string line;

    if (!playlist_file.is_open()) {
        std::cout << "PlaylistManager, retrive_data(), File is not open."
                  << std::endl;
        return;
    }

    while (std::getline(playlist_file, line)) {
        if (line.empty())
            continue;

        if (line.rfind("#EXTINF", 0) == 0) {
            if (!temp_lines.empty()) {
                ContentItem item = this->parse_data(temp_lines);
                this->insert_item(content, item);
            }
            temp_lines.clear();
        }

        temp_lines.push_back(line);
    }

    if (!temp_lines.empty()) {
        ContentItem item = this->parse_data(temp_lines);
        this->insert_item(content, item);
    }

    result = content;
    data_dispatcher.emit();
}