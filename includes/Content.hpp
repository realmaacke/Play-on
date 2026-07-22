#pragma once

#include "gtkmm/box.h"
#include <cstddef>
#include <optional>
#include <string>
#include <vector>

enum ContentType { serie, movie, channel };

struct ContentItem {
    std::string name;
    std::string image;
    std::string group;
    std::string url;
    std::optional<int> season = NULL;
    std::optional<int> episode = NULL;
};

struct ContainerContent {
    std::string content_name;
    std::string location;
    std::vector<ContentItem> children = {};
    ContentType *type = nullptr;
    Gtk::Box *content_view = nullptr; // filled in by build_grid
};

class Content {
  public:
    Content() = default;

    ContentItem find_content_item(std::string name);
    ContainerContent find_container(std::string name);

    void populate_content(std::vector<ContainerContent> array) {
        m_content = std::move(array);
    }

    std::vector<ContainerContent> get_all_content() { return this->m_content; }

    void delete_content() { m_content.clear(); }

    std::vector<ContainerContent> m_content;

  private:
};