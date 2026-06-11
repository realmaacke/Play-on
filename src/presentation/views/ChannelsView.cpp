#include "presentation/views/ChannelsView.hpp"
#include "gtkmm/label.h"
#include "gtkmm/object.h"

void ChannelsView::build_ui() {
    set_hexpand(true);
    set_vexpand(true);
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::FILL);

    m_title.set_label("Channels");

    append(m_title);
}