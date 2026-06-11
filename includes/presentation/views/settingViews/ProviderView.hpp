#pragma once
#include "presentation/views/settingViews/BaseSettingView.hpp"
#include <gtkmm.h>

class ProviderView : public BaseSettingView {
  public:
    ProviderView() : BaseSettingView("provider") {}

    void build_ui() override;

  private:
    std::string m_name;
};