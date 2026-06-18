#pragma once

#include "BaseView.hpp"

class MoviesView : public BaseView {

  public:
    MoviesView() : BaseView("movies") {}

  private:
    void build_ui() override;
    void load_xml() override;
};