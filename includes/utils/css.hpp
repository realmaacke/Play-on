#pragma once
#include <iostream>
#include <gtkmm.h>

inline void load_css(const std::string &path)
{
    auto css = Gtk::CssProvider::create();
    css->load_from_path(path);
    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(),
        css,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}