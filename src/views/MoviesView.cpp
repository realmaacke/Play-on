#include "views/MoviesView.hpp"
#include "gtkmm/box.h"

void MoviesView::load_xml() {}

void MoviesView::build_ui() {
    auto root = Gtk::Box();

    root.add_css_class("box-class");
    root.set_hexpand(true);
    root.set_vexpand(true);

    append(root);
}
