#include <future>
#include <gtkmm.h>
#include <vector>

#include "Application.hpp"
#include "Content.hpp"
#include "MainWindow.hpp"
#include "glibmm/refptr.h"
#include "processing/PlaylistManager.hpp"

int main(int argc, char *argv[]) {
    Glib::RefPtr<Application> app = Application::create();

    return app->run(argc, argv);
}
