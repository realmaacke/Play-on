#pragma once
#include <gtkmm.h>

class BaseSettingView : public Gtk::Box {
  public:
    BaseSettingView(const std::string &name) : m_name(name) {
        add_css_class("setting-page");
    }

    virtual void build_ui() = 0;
    const std::string &get_name() const { return m_name; }

  private:
    std::string m_name;
};