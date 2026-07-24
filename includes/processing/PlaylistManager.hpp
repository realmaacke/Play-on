#pragma once

#include "Content.hpp"
#include "glibmm/dispatcher.h"
#include <string>
#include <vector>

class PlaylistManager {

  public:
    PlaylistManager() {}
    std::vector<ContainerContent> content_template();
    std::string categorize_group(const std::string &group_title);

    void insert_item(std::vector<ContainerContent> &content, ContentItem item);

    ContentItem parse_data(std::vector<std::string> lines);

    void retrive_data();

    bool get_cache();

    Glib::Dispatcher data_dispatcher;
    // std::vector<ContainerContent> result;

    std::vector<ContainerContent> result{
        ContainerContent{.content_name = "Movies", .location = "movies"},
        ContainerContent{.content_name = "Series", .location = "series"},
        ContainerContent{.content_name = "Channels", .location = "channels"}};

    bool hasCached = false;

  private:
    std::string playlist_path; // This will change in future.
};