#include <iostream>

#include "MainWindow.hpp"

#include "gtkmm/object.h"
#include "presentation/views/BaseView.hpp"

#include "presentation/views/ChannelsView.hpp"
#include "presentation/views/MoviesView.hpp"
#include "presentation/views/SeriesView.hpp"
#include "presentation/views/SettingsView.hpp"
#include "presentation/views/Sidebar.hpp"
#include "utils/css.hpp"

MainWindow::MainWindow() : m_root(Gtk::Orientation::HORIZONTAL, 0) {
    // load base css.
    add_css_class("base");
    load_css("resources/base.css");

    this->build_ui();
}

void MainWindow::build_ui() {
    // Change this to some global struct or some cfg file.
    set_title("Playon IPTV");
    set_default_size(1280, 720);
    maximize();

    m_sidebar = Gtk::make_managed<Sidebar>(
        [this](const std::string &view) { navigate_to(view); });

    m_root.append(*m_sidebar);
    m_root.append(m_stack);

    m_views = {
        Gtk::make_managed<ChannelsView>(),
        Gtk::make_managed<MoviesView>(),
        Gtk::make_managed<SeriesView>(),
        Gtk::make_managed<SettingsView>(),
    };

    for (auto *view : m_views) {
        register_view(view);
    }

    set_child(m_root);
    navigate_to("channels");
}

void MainWindow::register_view(BaseView *view) {
    this->m_stack.add(*view, view->get_name());
    view->build_ui();
}

void MainWindow::navigate_to(const std::string &view) {
    bool show_sidebar = (view != "settings");

    m_sidebar->set_visible(show_sidebar);
    m_stack.set_visible_child(view);
}