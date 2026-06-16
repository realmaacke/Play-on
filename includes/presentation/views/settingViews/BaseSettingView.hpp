#pragma once
#include <gtkmm.h>

class BaseSettingView : public Gtk::Box {
  public:
    BaseSettingView(const std::string &name) : m_name(name) {
        add_css_class("setting-page");
    }

    virtual void build_ui() {};
    virtual void load_ui() {};
    const std::string &get_name() const { return m_name; }

  protected:
    Glib::RefPtr<Gtk::Builder> m_builder;

  private:
    std::string m_name;
};