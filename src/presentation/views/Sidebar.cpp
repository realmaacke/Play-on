#include "presentation/views/Sidebar.hpp"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/eventcontrollermotion.h"
#include "gtkmm/image.h"
#include "gtkmm/object.h"
#include <string>
#include <vector>

struct navigation_struct {
    std::string name;
    std::string icon;
    std::string css;
    std::string to_where;
};

std::vector<navigation_struct> nav_items = {
    {"Tv", "tv-symbolic", "sidebar-nav-item", "channels"},
    {"EPG", "view-calendar-symbolic", "sidebar-nav-item", "epg"},
    {"Movies", "video-x-generic-symbolic", "sidebar-nav-item", "movies"},
    {"Series", "applications-multimedia-symbolic", "sidebar-nav-item",
     "series"},
    {"Settings", "preferences-system-symbolic", "sidebar-nav-item",
     "settings"}};

void Sidebar::load_ui() {
    m_builder = Gtk::Builder::create_from_file("resources/ui/sidebar.ui");

    m_logo_image = m_builder->get_widget<Gtk::Image>("sidebar_logo_image");
    auto *logo_box = m_builder->get_widget<Gtk::Box>("sidebar_logo_box");

    m_nav_box = m_builder->get_widget<Gtk::Box>("sidebar_nav_box");

    append(*logo_box);
    append(*m_nav_box);

    // Styling
    this->set_orientation(Gtk::Orientation::VERTICAL);
    this->set_hexpand(false);
    this->set_vexpand(true);
    this->set_size_request(250, -1);

    this->build_ui();
}

void Sidebar::build_ui() {

    for (const auto &item : nav_items) {
        auto btn = Gtk::make_managed<Gtk::Button>();
        btn->set_hexpand(true);
        btn->set_size_request(-1, 52);
        btn->add_css_class(item.css);

        // Icon + label box inside button
        auto hbox =
            Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 12);
        hbox->set_halign(Gtk::Align::START);
        hbox->set_margin_start(4);

        auto icon = Gtk::make_managed<Gtk::Image>();
        icon->set_from_icon_name(item.icon);
        icon->set_pixel_size(24);
        icon->set_opacity(0.75);

        auto label = Gtk::make_managed<Gtk::Label>(item.name);
        label->set_halign(Gtk::Align::START);
        m_nav_labels.push_back(label);

        hbox->append(*icon);
        hbox->append(*label);
        btn->set_child(*hbox);

        btn->signal_clicked().connect([this, btn, item] {
            if (m_active_btn) {
                m_active_btn->remove_css_class("active");
            }

            btn->add_css_class("active");
            m_active_btn = btn;
            m_on_navigate(item.to_where);
        });

        m_nav_box->append(*btn);
    }
}

void Sidebar::setup_hover() {
    set_collapsed(true);
    auto motion = Gtk::EventControllerMotion::create();

    motion->signal_enter().connect(
        [this](double, double) { set_collapsed(false); });

    motion->signal_leave().connect([this]() { set_collapsed(true); });

    add_controller(motion);
}

void Sidebar::set_collapsed(bool collapsed) {
    m_collapsed = collapsed;

    if (collapsed) {
        remove_css_class("expanded");
        add_css_class("collapsed");
        set_size_request(64, -1);
        if (m_logo_image)
            m_logo_image->set_visible(false);
        for (auto *lbl : m_nav_labels)
            lbl->set_visible(false);
    } else {
        remove_css_class("collapsed");
        add_css_class("expanded");
        set_size_request(250, -1);
        if (m_logo_image)
            m_logo_image->set_visible(true);
        for (auto *lbl : m_nav_labels)
            lbl->set_visible(true);
    }
}