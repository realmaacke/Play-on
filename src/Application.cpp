#include "Application.hpp"
#include "LoadingWindow.hpp"
#include "MainWindow.hpp"
#include "glibmm/refptr.h"
#include "gtkmm/application.h"
#include "gtkmm/applicationwindow.h"
#include "gtkmm/window.h"
#include "processing/PlaylistManager.hpp"
#include "sigc++/functors/mem_fun.h"

Application::Application() : Gtk::Application("org.gtkm.playon") {
    player.data_dispatcher.connect(
        sigc::mem_fun(*this, &Application::on_data_ready));
}

Glib::RefPtr<Application> Application::create() {
    return Glib::RefPtr<Application>(new Application());
}

void Application::on_activate() {
    LoadingWindow *loader = new LoadingWindow();
    // MainWindow *window = new MainWindow();

    add_window(*loader);
    loader->present();

    std::thread worker(&PlaylistManager::retrive_data, &player);
    worker.detach();
}

void Application::on_data_ready() {
    Gtk::Window *active = get_active_window();

    if (active) {
        active->close();
    }

    MainWindow *actual_window = new MainWindow();

    add_window(*actual_window);
    actual_window->present();

    for (auto &item : player.result) {
        std::cout << item.name << std::endl;
    }
}