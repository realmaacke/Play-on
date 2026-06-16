#pragma once
#include "gtkmm/box.h"
#include "utils/css.hpp"
#include "utils/ui.hpp"
#include <gtkmm.h>
#include <string>

class BaseView : public Gtk::Box {
  public:
    BaseView(const std::string &name, const std::string &ui_path)
        : m_name(name), m_css_name(name), m_ui_path(ui_path) {
        add_css_class(this->m_name);
        load_css("views/" + name + ".css");

        if (!m_ui_path.empty()) {
            m_root = load_builder(m_ui_path)->get_widget<Gtk::Box>("root");

            validateUI(this->m_name + " root", m_root);
        }
    }

    virtual void build_ui() = 0;

    const std::string &get_name() const { return m_name; }
    const std::string &get_css_name() const { return m_css_name; }

    Gtk::Box *m_root;

  private:
    std::string m_name;
    std::string m_css_name;
    std::string m_ui_path;
};