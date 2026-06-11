#include "presentation/views/Sidebar.hpp"
#include "gtkmm/button.h"
#include "gtkmm/object.h"
#include <vector>

struct navigation_struct {
    std::string name;
    std::string css;
    std::string to_where;
};

std::vector<navigation_struct> nav_items = {
    {"Live Tv", "sidebar-nav-item", "channels"},
    {"Movies", "sidebar-nav-item", "movies"},
    {"Series", "sidebar-nav-item", "series"},
    {"Settings", "sidebar-nav-item", "settings"}};

void Sidebar::build_ui() {

    // 200 witdh, full height.
    set_size_request(200, -1);
    m_nav_items.set_orientation(Gtk::Orientation::VERTICAL);

    for (const auto &item : nav_items) {
        auto btn = Gtk::make_managed<Gtk::Button>(item.name);
        btn->add_css_class(item.css);
        btn->signal_clicked().connect(
            [this, item] { m_on_navigate(item.to_where); });

        m_nav_items.append(*btn);
    }

    append(m_nav_items);
}