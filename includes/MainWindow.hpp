#pragma once
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include <gtkmm.h>

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow();

  private:
    Gtk::Box m_root;
    Gtk::Box *m_sidebar;

    void initialize_screen();
    void build_ui();
};