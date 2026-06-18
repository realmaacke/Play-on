#include "views/MoviesView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/flowbox.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "gtkmm/scrolledwindow.h"
#include <iostream>
#include <string>
#include <vector>

struct mock_movie_struct {
    std::string name;
};

std::vector<mock_movie_struct> mock_movies = {
    {"Superman revenge of the sith"},
    {"Movie_02"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Batman the dark night"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Tennage mutant ninja turtles"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
    {"Movie_03"},
};

std::vector<mock_movie_struct> mock_movies1 = {
    {"Ninjago"},
    {"Star wars"},
    {"Movie_69"},
};

struct mock_categories_struct {
    std::string name;
    std::string location;
    std::vector<mock_movie_struct> movies;
    Gtk::Box *category_box = nullptr;
};

std::vector<mock_categories_struct> mock_categories = {
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

    // Header
    Gtk::Label *sidebar_category_title = Gtk::make_managed<Gtk::Label>();
    sidebar_category_title->set_label("Categories");

    m_sidebar_header->append(*sidebar_category_title);

    // Sidebar
    for (auto &item : mock_categories) {
        auto btn = Gtk::make_managed<Gtk::Button>(item.name);
        btn->add_css_class("movies_sidebar_nav_item");
        m_sidebar_nav->append(*btn);

        btn->signal_clicked().connect([this, btn, item] {
            if (m_active_btn) {
                m_active_btn->remove_css_class("active");
            }

            btn->add_css_class("active");
            m_active_btn = btn;

            navigate_to(item.location);
        });
    }
    // Register each category

    for (auto &category : mock_categories) {

        auto *scrollArea = Gtk::make_managed<Gtk::ScrolledWindow>();
        scrollArea->set_policy(Gtk::PolicyType::NEVER,
                               Gtk::PolicyType::AUTOMATIC);
        scrollArea->set_vexpand(true);

        auto *movie_grid = Gtk::make_managed<Gtk::FlowBox>();
        movie_grid->set_valign(Gtk::Align::START);
        movie_grid->set_max_children_per_line(20);
        movie_grid->set_min_children_per_line(1);
        movie_grid->set_row_spacing(16);
        movie_grid->set_column_spacing(16);
        movie_grid->set_selection_mode(Gtk::SelectionMode::NONE);
        movie_grid->set_hexpand(true);

        scrollArea->set_child(*movie_grid);

        category.category_box = Gtk::make_managed<Gtk::Box>();
        category.category_box->set_name(category.location);

        category.category_box->append(*scrollArea);

        for (auto &movie : category.movies) {
            auto *movie_container =
                Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 4);
            movie_container->add_css_class("movie_item_container");

            auto *movie_button = Gtk::make_managed<Gtk::Button>();
            movie_button->add_css_class("movie_item_button");

            auto *movie_image = Gtk::make_managed<Gtk::Image>();
            movie_image->property_file().set_value(
                "resources/images/mock_image.jpg");
            movie_image->set_pixel_size(150);
            movie_button->set_child(*movie_image);

            auto *movie_title = Gtk::make_managed<Gtk::Label>(movie.name);
            movie_title->add_css_class("movie_item_title");
            movie_title->set_ellipsize(Pango::EllipsizeMode::END);
            movie_title->set_max_width_chars(15);
            movie_title->set_halign(Gtk::Align::CENTER);

            movie_container->append(*movie_button);
            movie_container->append(*movie_title);
            movie_grid->append(*movie_container);
        }

        this->register_view(*category.category_box);
    }
}

void MoviesView::navigate_to(std::string view) {
    m_container->set_visible_child(view);
}

void MoviesView::register_view(Gtk::Box &view) {
    m_container->add(view, view.get_name());
}