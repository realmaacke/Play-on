#pragma once
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/flowbox.h"
#include <optional>
#include <string>
#include <utility>
#include <vector>

struct GridItem {
    std::string name;
    // Fill in more after need.
};

struct GridContent {
    std::string content_name;
    std::string location;
    std::vector<GridItem> children;
    Gtk::Box *content_view = nullptr; // filled in by build_grid, never touch this with other thread
};

class GridView {
  public:
    GridView() = default;
    void load_grid_content(std::vector<GridContent> content_array) {
        m_content = std::move(content_array);
    }
    void unload_grid_content() { m_content.clear(); }

    void build_grid(std::function<void(Gtk::Box &)> register_box);

    void build_sidebar(Gtk::Box *header, Gtk::Box *nav,
                       const std::string &header_title,
                       std::function<void(const std::string &)> on_navigate);

  private:
    void populate_grid(Gtk::FlowBox &grid, const GridContent &content);

    std::vector<GridContent> m_content;
    Gtk::Button *m_active_btn = nullptr;
};
