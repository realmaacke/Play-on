#pragma once
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/object.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Used for all ui.
inline Glib::RefPtr<Gtk::Builder> load_builder(const std::string &path) {
    return Gtk::Builder::create_from_file("resources/ui/" + path);
}

// used specificly for sidebars.
inline Gtk::Box *load_sidebar(const std::string &path) {
    auto builder = load_builder("sidebars/" + path);
    return builder->get_widget<Gtk::Box>("root");
}

// Checks wheter widgets is there.
inline void validateUI(const std::string &name, Gtk::Object *element) {
    if (!element) {
        throw std::runtime_error("Failed to load: " + name + " | undefined");
    }
}