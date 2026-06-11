#pragma once
#include "presentation/views/BaseView.hpp"
#include <functional>
#include <gtkmm.h>

class Sidebar : public BaseView {
  public:
    Sidebar(std::function<void(const std::string &)> on_navigate)
        : BaseView("sidebar", "sidebar"), m_on_navigate(on_navigate) {
        this->build_ui();
    }
    void build_ui() override;

  private:
    Gtk::Box m_nav_items;
    std::function<void(const std::string &)> m_on_navigate;
};