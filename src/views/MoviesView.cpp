#include "views/MoviesView.hpp"
#include "Content.hpp"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include <string>
#include <vector>

std::vector<ContentItem> mock_movies = {
    {"Superman revenge of the sith", "", "", ""},
    {"Movie_02", "", "", ""},
};
std::vector<ContentItem> mock_movies1 = {
    {
        "Ninjago",
        "",
        "",
        "",
    },
    {
        "Ninjago",
        "",
        "",
        "",
    },
    {
        "Ninjago",
        "",
        "",
        "",
    },
};
std::vector<ContainerContent> mock_categories_movies = {
    {"All", "all", mock_movies},
    {"Swedish", "swedish", mock_movies1},
    {"Nordic", "nordic", mock_movies},
    {"Other", "other", mock_movies},
};

void MoviesView::load_xml() {
    auto Builder = Gtk::Builder::create_from_file("resources/xml/movies.ui");

    Gtk::Box *root = Builder->get_widget<Gtk::Box>("root");

    m_sidebar = Builder->get_widget<Gtk::Box>("movies_sidebar");
    m_container = Builder->get_widget<Gtk::Stack>("movies_container");

    m_sidebar_header = Builder->get_widget<Gtk::Box>("movies_sidebar_header");
    m_sidebar_nav = Builder->get_widget<Gtk::Box>("movies_sidebar_nav");

    append(*root);
}

void MoviesView::build_ui() {
    populate_content(mock_categories_movies);
    build_sidebar(m_sidebar_header, m_sidebar_nav, "Movies",
                  [this](const std::string &loc) { navigate_to(loc); });
    build_grid([this](Gtk::Box &box) { register_view(box); });
}

void MoviesView::navigate_to(std::string view) {
    m_container->set_visible_child(view);
}

void MoviesView::register_view(Gtk::Box &view) {
    m_container->add(view, view.get_name());
}