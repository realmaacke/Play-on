#include "presentation/views/SettingsView.hpp"
#include "gtkmm/label.h"

void SettingsView::build_ui() {
    set_hexpand(true);
    set_vexpand(true);
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::FILL);

    m_title.set_label("Settings");

    append(m_title);
}