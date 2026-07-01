#pragma once
#include "Content.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/flowbox.h"
#include <string>

class GridView : public Content {
  public:
    GridView() = default;

    void build_grid(std::function<void(Gtk::Box &)> register_box);

    void build_sidebar(Gtk::Box *header, Gtk::Box *nav,
                       const std::string &header_title,
                       std::function<void(const std::string &)> on_navigate);

  private:
    void populate_grid(Gtk::FlowBox &grid, const ContainerContent &content);

    Gtk::Button *m_active_btn = nullptr;
};