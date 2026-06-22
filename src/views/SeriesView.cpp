#include "views/SeriesView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/flowbox.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "gtkmm/scrolledwindow.h"
#include <string>
#include <vector>

struct mock_series_struct {
    std::string name;
};

std::vector<mock_series_struct> mock_series = {
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

std::vector<mock_series_struct> mock_series1 = {
    {"Ninjago"},
    {"Star wars"},
    {"Movie_69"},
};

struct mock_categories_struct {
    std::string name;
    std::string location;
    std::vector<mock_series_struct> movies;
    Gtk::Box *category_box = nullptr;
};

std::vector<mock_categories_struct> mock_categories_series = {
    {"All", "all", mock_series},
    {"Swedish", "swedish", mock_series1},
    {"Nordic", "nordic", mock_series},
    {"Other", "other", mock_series},
};

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

    // Header
    Gtk::Label *sidebar_category_title = Gtk::make_managed<Gtk::Label>();
    sidebar_category_title->set_label("Categories for series");

    m_sidebar_header->append(*sidebar_category_title);

    // Sidebar
    for (auto &item : mock_categories_series) {
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

    for (auto &category : mock_categories_series) {

        auto *scrollArea = Gtk::make_managed<Gtk::ScrolledWindow>();
        scrollArea->set_policy(Gtk::PolicyType::NEVER,
                               Gtk::PolicyType::AUTOMATIC);
        scrollArea->set_vexpand(true);

        auto *content_grid = Gtk::make_managed<Gtk::FlowBox>();
        content_grid->set_valign(Gtk::Align::START);
        content_grid->set_max_children_per_line(20);
        content_grid->set_min_children_per_line(1);
        content_grid->set_row_spacing(16);
        content_grid->set_column_spacing(16);
        content_grid->set_selection_mode(Gtk::SelectionMode::NONE);
        content_grid->set_hexpand(true);

        scrollArea->set_child(*content_grid);

        category.category_box = Gtk::make_managed<Gtk::Box>();
        category.category_box->set_name(category.location);

        category.category_box->append(*scrollArea);

        for (auto &movie : category.movies) {
            auto *item_container =
                Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 4);
            item_container->add_css_class("movie_item_container");

            auto *item_button = Gtk::make_managed<Gtk::Button>();
            item_button->add_css_class("movie_item_button");

            auto *item_image = Gtk::make_managed<Gtk::Image>();
            item_image->property_file().set_value(
                "resources/images/mock_image.jpg");
            item_image->set_pixel_size(150);
            item_button->set_child(*item_image);

            auto *item_title = Gtk::make_managed<Gtk::Label>(movie.name);
            item_title->add_css_class("movie_item_title");
            item_title->set_ellipsize(Pango::EllipsizeMode::END);
            item_title->set_max_width_chars(15);
            item_title->set_halign(Gtk::Align::CENTER);

            item_container->append(*item_button);
            item_container->append(*item_title);
            content_grid->append(*item_container);
        }

        this->register_view(*category.category_box);
    }
}

void SeriesView::navigate_to(std::string view) {
    m_container->set_visible_child(view);
}

void SeriesView::register_view(Gtk::Box &view) {
    m_container->add(view, view.get_name());
}