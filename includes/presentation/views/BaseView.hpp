#pragma once
#include <gtkmm.h>

#include "utils/css.hpp"

class BaseView : public Gtk::Box
{
public:
    BaseView(const std::string &name, const std::string &css_class)
        : m_name(name), m_css_name(css_class)
    {
        add_css_class(css_class);
        load_css("resources/views/" + name + ".css");
    }

    virtual void build_ui() = 0;
    const std::string &get_name() const { return m_name; }
    const std::string &get_css_name() const {return m_css_name; }

private:
    std::string m_name;
    std::string m_css_name;
};