#pragma once
#include "gtkmm/box.h"
#include "gtkmm/label.h"
#include "gtkmm/widget.h"
#include "presentation/views/BaseView.hpp"
#include "presentation/views/settingViews/BaseSettingView.hpp"
#include <gtkmm.h>
#include <string>
#include <unordered_map>

class SettingsView : public BaseView {
  public:
    SettingsView() : BaseView("settings", "settings") {}
    void build_ui() override;
    void load_ui() override;

  private:
    Gtk::Box *m_inner_sidebar = nullptr;
    Gtk::Box *m_nav_box = nullptr;
    Gtk::Stack *m_stack = nullptr;

    std::vector<BaseSettingView *> m_pages;

    std::unordered_map<std::string, Gtk::Widget *> m_page_map;

    void register_view(BaseSettingView *view);

    void navigate_to(const std::string &page);
    void add_section(const std::string &label, const std::string &icon_name,
                     const std::string &page);
};