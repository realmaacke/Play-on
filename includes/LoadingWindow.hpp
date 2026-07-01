#pragma once
#include "Config.hpp"
#include "utils/css.hpp"
#include <gtkmm.h>

class LoadingWindow : public Gtk::Window {
  public:
    LoadingWindow() {
        set_title(Config::APP_NAME);
        set_default_size(Config::APP_WIDTH, Config::APP_HEIGHT);

        add_css_class("base");
        load_css("base");

        if (Config::APP_MAXIMIZE) {
            maximize();
        }

        spinner.start();
        spinner.add_css_class("loading-spinner");
        box.append(spinner);
        set_child(box);
    }

  private:
    Gtk::Box box{Gtk::Orientation::VERTICAL};
    Gtk::Spinner spinner;
};