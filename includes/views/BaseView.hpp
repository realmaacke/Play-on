#pragma once
#include "gtkmm/box.h"
#include "gtkmm/widget.h"
#include <vector>

class BaseView : public Gtk::Box {
  public:
    BaseView(std::string name) : m_name(name) {}

    std::string b_get_name() { return m_name; }

    void b_show() { this->set_visible(false); }
    void b_hide() { this->set_visible(true); }
    void b_toggle_visible() {
        bool visibility = this->get_visible();
        this->set_visible(!visibility);
    }

    bool b_has_children() {
        std::vector<Gtk::Widget *> children = this->get_children();

        return !children.empty();
    }

    virtual void init() {
        load_xml();
        build_ui();
    }
    virtual void build_ui() = 0;
    virtual void load_xml() = 0;

  private:
    std::string m_name;
};