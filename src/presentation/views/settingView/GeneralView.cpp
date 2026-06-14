#include "presentation/views/settingViews/GeneralView.hpp"
#include "gtkmm/box.h"

void GeneralView::load_ui() {
    m_builder =
        Gtk::Builder::create_from_file("resources/ui/settingsPages/general.ui");

    auto *root = m_builder->get_widget<Gtk::Box>("general_root");

    append(*root);
    this->build_ui();
}

void GeneralView::build_ui() {
    set_orientation(Gtk::Orientation::HORIZONTAL);
    set_hexpand(true);
    set_vexpand(true);
    set_size_request(-1, -1);

    add_css_class("settings-general");

    auto label = Gtk::make_managed<Gtk::Label>();

    append(*label);
}