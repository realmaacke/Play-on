#pragma once

#include "views/BaseView.hpp"
class Sidebar : public BaseView {
  public:
    Sidebar(std::function<void(const std::string &)> on_navigate)
        : BaseView("sidebar", "sidebar.ui"), m_on_navigate(on_navigate) {}

    void build_ui() override;

  private:
    void setup_hover();
    void set_collapsed(bool collapsed);

    Gtk::Button *m_active_btn = nullptr;
    std::vector<Gtk::Label *> m_nav_labels;
    bool m_collapsed = true;

    std::function<void(const std::string &)> m_on_navigate;
};