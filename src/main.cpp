#include "Application.hpp"
#include "glibmm/refptr.h"
#include <gtkmm.h>

#include "Database.hpp"

#include <sqlite3.h>

int main(int argc, char *argv[]) {

    Database db;

    db.open("database.db");

    Glib::RefPtr<Application> app = Application::create();

    return app->run(argc, argv);
}
