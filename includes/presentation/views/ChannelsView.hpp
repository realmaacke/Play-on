#pragma once
#include "gtkmm/label.h"
#include "presentation/views/BaseView.hpp"
#include <gtkmm.h>

class ChannelsView : public BaseView {
  public:
    ChannelsView() : BaseView("channels", "channels") {}
    void build_ui() override;

  private:
    Gtk::Label m_title;
};