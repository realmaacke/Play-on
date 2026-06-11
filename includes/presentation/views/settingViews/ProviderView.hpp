#pragma once
#include "gtkmm/box.h"
#include "gtkmm/widget.h"
#include "presentation/views/settingViews/BaseSettingView.hpp"
#include <gtkmm.h>
#include <vector>

struct Provider {
    std::string name;
    std::string type; // "credentials" or "m3u"
};

class ProviderView : public BaseSettingView {
  public:
    ProviderView() : BaseSettingView("provider") {}

    void build_ui() override;

  private:
    std::string m_name;
    Gtk::Stack m_stack;
    Gtk::Box m_providers_list;
    Gtk::Stack m_input_stack;

    std::vector<Provider> m_providers;

    Gtk::Box *build_provider_management();
    Gtk::Box *build_provider_list();
    void add_provider_row(const Provider &p);
    void refresh_list();
};