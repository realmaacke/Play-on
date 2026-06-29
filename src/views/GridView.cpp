#include "views/GridView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/flowbox.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "gtkmm/scrolledwindow.h"
#include <iostream>
#include <string>
#include <utility>

void GridView::build_sidebar(
    Gtk::Box *header, Gtk::Box *nav, const std::string &header_title,
    std::function<void(const std::string &)> on_navigate) {
    if (m_content.empty()) {
        std::cout << "Content is empty" << std::endl;
        return;
    }

    Gtk::Label *title_label = Gtk::make_managed<Gtk::Label>();
    title_label->set_label(header_title);
    header->append(*title_label);

    for (GridContent &item : m_content) {
        Gtk::Button *button = Gtk::make_managed<Gtk::Button>();
        button->set_label(item.content_name);
        button->add_css_class("sidebar_nav_item");
        nav->append(*button);

        button->signal_clicked().connect(
            [this, button, location = item.location, on_navigate] {
                if (m_active_btn) {
                    m_active_btn->remove_css_class("active");
                }
                button->add_css_class("active");
                m_active_btn = button;

                on_navigate(location);
            });
    }
}

void GridView::build_grid(std::function<void(Gtk::Box &)> register_box) {

    for (GridContent &content : m_content) {
        // Scrollable area
        Gtk::ScrolledWindow *scroll = Gtk::make_managed<Gtk::ScrolledWindow>();

        scroll->set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
        scroll->set_vexpand(true);

        // Grid area, (put onto the scrollable area)
        Gtk::FlowBox *grid = Gtk::make_managed<Gtk::FlowBox>();

        grid->set_valign(Gtk::Align::START);

        grid->set_max_children_per_line(20);
        grid->set_min_children_per_line(1);
        grid->set_row_spacing(16);
        grid->set_column_spacing(16);
        grid->set_selection_mode(Gtk::SelectionMode::NONE);
        grid->set_hexpand(true);

        scroll->set_child(*grid);

        content.content_view = Gtk::make_managed<Gtk::Box>();
        content.content_view->set_name(content.location);
        content.content_view->append(*scroll);

        populate_grid(*grid, content);
        register_box(*content.content_view);
    }
}

void GridView::populate_grid(Gtk::FlowBox &grid, const GridContent &content) {
    for (const GridItem &item : content.children) {
        Gtk::Box *item_wrapper = Gtk::make_managed<Gtk::Box>();
        item_wrapper->set_orientation(Gtk::Orientation::VERTICAL);
        item_wrapper->set_spacing(4);
        item_wrapper->add_css_class("grid_item_wrapper");

        Gtk::Button *item_button = Gtk::make_managed<Gtk::Button>();
        item_button->add_css_class("grid_item_button");

        Gtk::Image *item_image = Gtk::make_managed<Gtk::Image>();
        // This will be a curl later on.
        item_image->property_file().set_value(
            "resources/images/mock_image.jpg");
        item_image->set_pixel_size(150);
        item_button->set_child(*item_image);

        Gtk::Label *item_title = Gtk::make_managed<Gtk::Label>(item.name);
        item_title->add_css_class("grid_item_title");
        item_title->set_ellipsize(Pango::EllipsizeMode::END);
        item_title->set_max_width_chars(15);
        item_title->set_halign(Gtk::Align::CENTER);

        item_wrapper->append(*item_button);
        item_wrapper->append(*item_title);

        grid.append(*item_wrapper);
    }
}
