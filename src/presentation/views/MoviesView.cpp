#include "presentation/views/MoviesView.hpp"
#include "gtkmm/label.h"

void MoviesView::build_ui() {
    set_hexpand(true);
    set_vexpand(true);
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::FILL);

    m_title.set_label("Movies");

    append(m_title);
}