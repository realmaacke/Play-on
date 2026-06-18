#include "views/MoviesView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include <iostream>
#include <string>
#include <vector>

struct mock_movie_struct {
    std::string name;
};

std::vector<mock_movie_struct> mock_movies = {
    {"Movie_01"},
    {"Movie_02"},
    {"Movie_03"},
};

struct mock_categories_struct {
    std::string name;
    std::string location;
    std::vector<mock_movie_struct> movies;
    Gtk::Box *category_box = nullptr;
};

std::vector<mock_categories_struct> mock_categories = {
    {"All", "all", mock_movies},
    {"Swedish", "swedish", mock_movies},
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
        category.category_box = Gtk::make_managed<Gtk::Box>();
        category.category_box->set_name(category.location);

        category.category_box->add_css_class("movies_category");

        auto *lbl = Gtk::make_managed<Gtk::Label>(category.name);

        category.category_box->append(*lbl);

        this->register_view(*category.category_box);
    }

    for (auto &x : m_container->get_children()) {
        std::cout << "Category: " << x->get_name() << std::endl;
    }
}

void MoviesView::navigate_to(std::string view) {
    m_container->set_visible_child(view);
}

void MoviesView::register_view(Gtk::Box &view) {
    m_container->add(view, view.get_name());
}