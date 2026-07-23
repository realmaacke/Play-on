#include "views/SeriesView.hpp"
#include "Content.hpp"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include <string>
#include <vector>

void SeriesView::load_xml() {
    auto Builder = Gtk::Builder::create_from_file("resources/xml/series.ui");

    Gtk::Box *root = Builder->get_widget<Gtk::Box>("root");

    m_sidebar = Builder->get_widget<Gtk::Box>("series_sidebar");
    m_container = Builder->get_widget<Gtk::Stack>("series_container");

    m_sidebar_header = Builder->get_widget<Gtk::Box>("series_sidebar_header");
    m_sidebar_nav = Builder->get_widget<Gtk::Box>("series_sidebar_nav");

    append(*root);
}

void SeriesView::build_ui() {
    populate_content(this->m_player->result);
    build_sidebar(m_sidebar_header, m_sidebar_nav, "Series",
                  [this](const std::string &loc) { navigate_to(loc); });
    build_grid([this](Gtk::Box &box) { register_view(box); });
}

void SeriesView::navigate_to(std::string view) {
    m_container->set_visible_child(view);
}

void SeriesView::register_view(Gtk::Box &view) {
    m_container->add(view, view.get_name());
}