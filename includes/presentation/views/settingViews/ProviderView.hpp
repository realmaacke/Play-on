#pragma once
#include "gtkmm/box.h"
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
    void load_ui() override;

  private:
    std::string m_name;
    Gtk::Stack *m_stack = nullptr;
    Gtk::Box *m_providers_list = nullptr;
    Gtk::Stack *m_input_stack = nullptr;

    std::vector<Provider> m_providers;
};