#include "Sidebar.hpp"
#include "glibmm/main.h"
#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/eventcontrollermotion.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "gtkmm/root.h"
#include "gtkmm/widget.h"
#include <cstdlib>
#include <iostream>

struct sidebar_item_struct {
    std::string name;
    std::string icon;
    std::string location;
};

std::vector<sidebar_item_struct> nav_items = {
    {"Tv", "tv-symbolic", "channels"},
    {"EPG", "view-calendar-symbolic", "epg"},
    {"Movies", "video-x-generic-symbolic", "movies"},
    {"Series", "applications-multimedia-symbolic", "series"},
    {"Settings", "preferences-system-symbolic", "settings"}};

void Sidebar::load_xml() {
    auto Builder = Gtk::Builder::create_from_file("resources/xml/sidebar.ui");

    Gtk::Box *root = Builder->get_widget<Gtk::Box>("root");

    m_logo = Builder->get_widget<Gtk::Image>("sidebar_logo_image");

    m_nav_box = Builder->get_widget<Gtk::Box>("sidebar_nav_box");

    append(*root);
}

void Sidebar::build_ui() {
    this->set_orientation(Gtk::Orientation::VERTICAL);
    this->set_hexpand(false);
    this->set_vexpand(true);
    this->set_size_request(250, -1);
    this->set_halign(Gtk::Align::START);

    for (const sidebar_item_struct &item : nav_items) {
        Gtk::Button *button = Gtk::make_managed<Gtk::Button>();
        button->set_hexpand(true);
        button->set_size_request(-1, 52);
        button->add_css_class("sidebar-nav-item");

        Gtk::Box *hbox =
            Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 12);
        hbox->set_halign(Gtk::Align::START);
        hbox->set_margin_start(4);

        Gtk::Image *icon = Gtk::make_managed<Gtk::Image>();
        icon->set_from_icon_name(item.icon);
        icon->set_pixel_size(24);
        icon->set_opacity(0.75);

        Gtk::Label *label = Gtk::make_managed<Gtk::Label>(item.name);
        label->set_halign(Gtk::Align::START);
        m_labels.push_back(label);

        hbox->append(*icon);
        hbox->append(*label);

        button->set_child(*hbox);

        button->signal_clicked().connect([this, button, item] {
            if (m_active) {
                m_active->remove_css_class("active");
            }

            button->add_css_class("active");
            m_active = button;
            m_on_navigate(item.location);
        });

        m_nav_box->append(*button);
    }
}

/*
 * Setup hover adds an event listener,
 * When mouse is inside *this which is sidebar,
 * toggle collapsed.
 */
void Sidebar::setup_hover() {
    this->set_collapsed(true);

    Glib::RefPtr<Gtk::EventControllerMotion> motion =
        Gtk::EventControllerMotion::create();

    motion->signal_enter().connect(
        [this](double, double) { this->set_collapsed(false); });

    motion->signal_leave().connect([this]() { set_collapsed(true); });

    add_controller(motion);
}

void Sidebar::set_collapsed(bool isCollapsed) {
    m_isCollapsed = isCollapsed;

    if (m_logo) {
        m_logo->set_visible(!isCollapsed);
    }

    for (Gtk::Label *label : m_labels) {
        label->set_visible(!isCollapsed);
    }

    remove_css_class(isCollapsed ? "expanded" : "collapsed");
    add_css_class(isCollapsed ? "collapsed" : "expanded");

    // set_size_request(isCollapsed ? 64 : 250, -1);

    this->animate_to(isCollapsed ? 64 : 250);
}

void Sidebar::animate_to(int target) {
    m_anim_target = target;
    m_anim_timer.disconnect();

    m_anim_timer = Glib::signal_timeout().connect(
        [this]() {
            int current = this->get_width();
            int delta = m_anim_target - current;

            int step = delta / 8;

            if (std::abs(delta) < 3) {
                this->set_size_request(m_anim_target, -1);
                return false;
            }
            this->set_size_request(current + step, -1);
            return true;
        },
        16);
}