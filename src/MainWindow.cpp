#include <gtkmm/label.h>
#include <gtkmm/object.h>
#include <iostream>

#include "MainWindow.hpp"
#include "gtkmm/box.h"
#include "utils/css.hpp"
#include "utils/ui.hpp"

#include "Config.hpp"

MainWindow::MainWindow() {
    add_css_class("base");
    load_css("base.css");

    this->initialize_screen();
}

void MainWindow::initialize_screen() {
    set_title(Config::WINDOW_TITLE);

    set_default_size(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);

    if (Config::WINDOW_MAXIMIZED) {
        maximize();
    }

    this->build_ui();
    set_child(m_root);
}

void MainWindow::build_ui() {
    Gtk::Box *root =
        load_builder("mainwindow.ui")->get_widget<Gtk::Box>("m_root");

    validateUI("root", root);
}