#include <iostream>

#include "presentation/views/HomeView.hpp"
#include "gtkmm/enums.h"

void HomeView::build_ui()
{
    // Allow for horizontal and vertical extra space.
    // Also fills all space.
    m_grid.add_css_class("home-view-grid");


    set_hexpand(true);
    set_vexpand(true);
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::FILL);

    m_center_box.set_halign(Gtk::Align::CENTER);
    m_center_box.set_valign(Gtk::Align::CENTER);
    m_center_box.set_orientation(Gtk::Orientation::VERTICAL);
    m_center_box.set_hexpand(true);
    m_center_box.set_vexpand(true);

    m_center_box.add_css_class("home-view-center-box");

    m_title.set_text("Play-on Client");
    m_title.set_halign(Gtk::Align::CENTER);
    m_title.add_css_class("home-title");

    this->add_card("Channels", "channels");
    this->add_card("Movies", "movies");

    this->add_card("Series", "series");
    this->add_card("settings", "settings");

    m_center_box.append(m_title);
    m_center_box.append(m_grid);
    append(m_center_box);
}

void HomeView::add_card(const std::string &label, const std::string &view)
{
    auto card = Gtk::make_managed<Gtk::Button>();

    card->set_size_request(140, 140);
    card->add_css_class("home-card");

    auto box = Gtk::make_managed<Gtk::Box>(
        Gtk::Orientation::VERTICAL,
        12
    );
    box->set_halign(Gtk::Align::CENTER);
    box->set_valign(Gtk::Align::CENTER);

    auto text_label = Gtk::make_managed<Gtk::Label>(label);
    text_label->add_css_class("home-card-label");

    box->append(*text_label);
    card->set_child(*box);

    card->signal_clicked()
        .connect([this, view]() {
            signal_navigate.emit(view);
        }
    );

    m_grid.append(*card);
}