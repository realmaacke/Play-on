#pragma once

#include "BaseView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/stack.h"

#include "views/GridView.hpp"
#include <vector>

class SeriesView : public BaseView, public GridView {

  public:
    SeriesView() : BaseView("series") {}

  private:
    void build_ui() override;
    void load_xml() override;

    void navigate_to(std::string view);
    void register_view(Gtk::Box &view);

    // Sidebar
    Gtk::Box *m_sidebar = nullptr;
    Gtk::Box *m_sidebar_header = nullptr;
    Gtk::Box *m_sidebar_nav = nullptr;
    Gtk::Button *m_active_btn = nullptr;

    // Content
    std::vector<Gtk::Box *> m_container_views;
    Gtk::Stack *m_container = nullptr;
};