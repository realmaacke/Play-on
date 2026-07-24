#include "Application.hpp"
#include "MainWindow.hpp"
#include "glibmm/refptr.h"
#include <gtkmm.h>

#include "Database.hpp"
#include "gtkmm/application.h"

#include <sqlite3.h>

int main(int argc, char *argv[]) {
    // Glib::RefPtr<Application> app = Application::create();

    Glib::RefPtr<Gtk::Application> application =
        Gtk::Application::create("com.example.playon");

    return application->make_window_and_run<MainWindow>(argc, argv);
}
