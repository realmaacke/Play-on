#pragma once
#include "presentation/views/settingViews/BaseSettingView.hpp"
#include <gtkmm.h>

class AccountView : public BaseSettingView {
  public:
    AccountView() : BaseSettingView("account") {}

    void build_ui() override;

  private:
    std::string m_name;
};