#include "processing/PlaylistManager.hpp"
#include "Content.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

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
        if (iter.content_name == "unknown") {
            iter.children.emplace_back(std::move(item));
            return;
        }
    }
}

std::vector<ContainerContent> PlaylistManager::content_template() {
    return std::vector<ContainerContent>{{"channels", "channels"},
                                         {"movies", "movies"},
                                         {"series", "series"},
                                         {"unknown", "unknown"}};
}

ContentItem PlaylistManager::parse_data(std::vector<std::string> lines) {
    static const std::regex name_re(R"re(tvg-name="([^"]*)")re");
    static const std::regex logo_re(R"re(tvg-logo="([^"]*)")re");
    static const std::regex group_re(R"re(group-title="([^"]*)")re");
    static const std::regex url_re(R"re((https?://[^\s"]+))re");

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

    std::string group = group_title;
    size_t dash_pos = group_title.find(" - ");
    if (dash_pos != std::string::npos) {
        group = group_title.substr(0, dash_pos);
    }

    return ContentItem{name, logo, group, url};
}

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