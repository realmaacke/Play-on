#pragma once
#include "Sidebar.hpp"
#include "views/BaseView.hpp"
#include <gtkmm.h>

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow();

  private:
    Sidebar *m_sidebar = nullptr;
    Gtk::Box m_root;
    Gtk::Stack m_stack;

    std::vector<BaseView *> m_views;

    void register_view(BaseView *view);
    void build_ui();

    void navigate_to(const std::string &view);
};