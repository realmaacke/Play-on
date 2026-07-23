#include "Database.hpp"
#include <iostream>
#include <sqlite3.h>

bool Database::open(const std::string &path) {
    int result = sqlite3_open_v2(path.c_str(), &this->db,
                                 SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
                                     SQLITE_OPEN_FULLMUTEX,
                                 nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Problem opening Database, path: " + path << std::endl;
        return false;
    }

    return true;
}