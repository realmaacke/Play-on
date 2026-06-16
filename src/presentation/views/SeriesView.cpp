#include "presentation/views/SeriesView.hpp"
#include "gtkmm/label.h"

void SeriesView::load_ui() {}

void SeriesView::build_ui() {
    set_hexpand(true);
    set_vexpand(true);
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::FILL);

    m_title.set_label("Series");

    append(m_title);
}