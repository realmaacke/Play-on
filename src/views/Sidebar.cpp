#include "views/Sidebar.hpp"

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

void Sidebar::build_ui() {}