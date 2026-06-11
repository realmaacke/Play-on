#pragma once
#include "presentation/views/BaseView.hpp"
#include "presentation/views/Sidebar.hpp"
#include <gtkmm.h>
#include <vector>

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow();

  private:
    Gtk::Box m_root;
    Gtk::Stack m_stack;

    Sidebar *m_sidebar = nullptr;

    // Stack
    std::vector<BaseView *> m_views;

    void register_view(BaseView *view);
    void build_ui();

    void navigate_to(const std::string &view);
};