#pragma once
#include "presentation/views/settingViews/BaseSettingView.hpp"
#include <gtkmm.h>

class GeneralView : public BaseSettingView {
  public:
    GeneralView() : BaseSettingView("general") {}

    void build_ui() override;

  private:
    std::string m_name;
};