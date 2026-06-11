#pragma once
#include "gtkmm/label.h"
#include "presentation/views/BaseView.hpp"
#include <gtkmm.h>

class SettingsView : public BaseView {
  public:
    SettingsView() : BaseView("settings", "settings") {}
    void build_ui() override;

  private:
    Gtk::Label m_title;
};