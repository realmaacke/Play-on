#include "presentation/views/settingViews/ProviderView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"

void ProviderView::load_ui() {
    m_builder = Gtk::Builder::create_from_file(
        "resources/ui/settingsPages/provider.ui");

    auto *root = m_builder->get_widget<Gtk::Box>("provider_root");

    append(*root);
}

void ProviderView::build_ui() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_hexpand(true);
    set_vexpand(true);
    add_css_class("settings-provider");
}
