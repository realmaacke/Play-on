#pragma once
#include "gtkmm/label.h"
#include "presentation/views/BaseView.hpp"
#include <gtkmm.h>

class MoviesView : public BaseView {
  public:
    MoviesView() : BaseView("movies", "movies") {}
    void build_ui() override;

  private:
    Gtk::Label m_title;
};