#include "processing/PlaylistManager.hpp"
#include "utils/parsing.hpp"
#include <fstream>
#include <iostream>

// Insert into ContainerContent, if no match is found, use movies.
void PlaylistManager::insert_item(
    std::vector<ContainerContent> &content, ContentItem item) {
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

    if (lower.find("seri") != std::string::npos)
        return "series";

    if (lower.find("movie") != std::string::npos)
        return "movies";

    if (lower.find("tv") != std::string::npos ||
        lower.find("channel") != std::string::npos ||
        lower.find("live") != std::string::npos)
        return "channels";

    return "movies";
}

// Regex to capture each property.
ContentItem PlaylistManager::parse_data(std::vector<std::string> lines) {
    std::string name, logo, group_title, url;

    for (std::string &line : lines) {
        if (line.find("tvg-name=") != std::string::npos)
            name = get_attribute(line, "tvg-name");

        if (line.find("tvg-logo=") != std::string::npos)
            logo = get_attribute(line, "tvg-logo");

        if (line.find("group-title=") != std::string::npos)
            group_title = get_attribute(line, "group-title");

        if (line.starts_with("http"))
            url = line;
    }

    std::string group = this->categorize_group(group_title);

    ContentItem returnItem;

    returnItem.name = name;
    returnItem.image = logo;
    returnItem.group = group;
    returnItem.url = url;

    // Captures season + episode
    if (group == "series") {
        get_episode_info(group_title, returnItem.season, returnItem.episode);
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