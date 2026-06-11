#include <iostream>
#include <gtkmm.h>

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    auto application_window = Gtk::Application::create("com.example.play-on");

    return application_window->make_window_and_run<MainWindow>(argc, argv);
}
