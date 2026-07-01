#pragma once
#include "glibmm/refptr.h"
#include "gtkmm/application.h"
#include "processing/PlaylistManager.hpp"
class Application : public Gtk::Application {

  protected:
    Application();

  protected:
    void on_activate() override;

  public:
    static Glib::RefPtr<Application> create();

  private:
    PlaylistManager player;
    void on_data_ready();
};