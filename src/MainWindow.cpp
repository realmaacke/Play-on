#include "MainWindow.hpp"
#include "Config.hpp"
#include "Sidebar.hpp"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include "processing/PlaylistManager.hpp"
#include "utils/css.hpp"
#include "views/BaseView.hpp"

#include "views/MoviesView.hpp"
#include "views/SeriesView.hpp"
#include <vector>

MainWindow::MainWindow(PlaylistManager &player)
    : m_root(Gtk::Orientation::HORIZONTAL, 0), m_player(&player) {

    set_title(Config::APP_NAME);
    set_default_size(Config::APP_WIDTH, Config::APP_HEIGHT);

    for (auto &x : this->m_player->result) {
        std::cout << x.content_name << std::endl;
    }

    if (Config::APP_MAXIMIZE) {
        maximize();
    }

    m_views = {Gtk::make_managed<MoviesView>(),
               Gtk::make_managed<SeriesView>()};

    for (auto &view : m_views) {
        register_view(view);
    }

    m_sidebar = Gtk::make_managed<Sidebar>(
        [this](const std::string &view) { navigate_to(view); });

    // Root holds sidebar + stack

    m_root.append(*m_sidebar);
    m_root.append(m_stack);

    m_stack.set_hexpand(true);

    set_child(m_root);

    this->build_ui();

    navigate_to("movies");
}
void MainWindow::build_ui() {
    add_css_class("base");
    load_css("base");
}

void MainWindow::register_view(BaseView *view) {
    view->init();
    m_stack.add(*view, view->b_get_name());
}

void MainWindow::navigate_to(const std::string &view) {
    m_stack.set_visible_child(view);
}