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

    Glib::Dispatcher data_dispatcher;
    std::vector<ContainerContent> result;

  private:
    std::string playlist_path; // This will change in future.
};