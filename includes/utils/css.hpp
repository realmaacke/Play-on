#pragma once
#include "gdkmm/display.h"
#include "gtk/gtk.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/stylecontext.h"
#include <string>

inline void load_css(const std::string &path) {
    auto css = Gtk::CssProvider::create();
    css->load_from_path("resources/" + path);
    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(), css,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}