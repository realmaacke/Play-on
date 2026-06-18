#pragma once
#include <functional>
#include <vector>

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "sigc++/connection.h"
#include "views/BaseView.hpp"

#include "utils/css.hpp"

class Sidebar : public Gtk::Box {
  public:
    Sidebar(std::function<void(const std::string &)> on_navigate)
        : m_on_navigate(on_navigate) {
        this->load_xml();
        this->build_ui();

        load_css("css/sidebar");
        setup_hover();
    }

    void load_xml();
    void build_ui();

  private:
    void setup_hover();
    void set_collapsed(bool isCollapsed);

    void animate_to(int target);

    Gtk::Box *m_nav_box = nullptr;
    Gtk::Image *m_logo = nullptr;

    Gtk::Button *m_active = nullptr;
    std::vector<Gtk::Label *> m_labels;
    bool m_isCollapsed = true;
    std::function<void(const std::string &)> m_on_navigate;

    // Animations for the slide
    sigc::connection m_anim_timer;
    int m_anim_target = 64;
};