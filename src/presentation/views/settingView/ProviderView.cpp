#include "presentation/views/settingViews/ProviderView.hpp"

void ProviderView::build_ui() {
    set_orientation(Gtk::Orientation::HORIZONTAL);
    set_hexpand(true);
    set_vexpand(true);
    set_size_request(-1, -1);

    add_css_class("settings-provider");

    auto label = Gtk::make_managed<Gtk::Label>();

    append(*label);
}