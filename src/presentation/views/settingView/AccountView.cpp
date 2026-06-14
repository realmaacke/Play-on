
#include "presentation/views/settingViews/AccountView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"

void AccountView::load_ui() {
    m_builder =
        Gtk::Builder::create_from_file("resources/ui/settingsPages/account.ui");

    auto *root = m_builder->get_widget<Gtk::Box>("account_root");

    append(*root);

    this->build_ui();
}

void AccountView::build_ui() {
    set_orientation(Gtk::Orientation::HORIZONTAL);
    set_hexpand(true);
    set_vexpand(true);
    set_size_request(-1, -1);

    add_css_class("settings-account");

    auto label = Gtk::make_managed<Gtk::Label>();

    append(*label);
}