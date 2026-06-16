#pragma once
#include "gtkmm/label.h"
#include "presentation/views/BaseView.hpp"
#include <gtkmm.h>

class SeriesView : public BaseView {
  public:
    SeriesView() : BaseView("series", "series") {}
    void build_ui() override;
    void load_ui() override;

  private:
    Gtk::Label m_title;
};