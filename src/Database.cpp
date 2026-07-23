#include "Database.hpp"
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <sstream>

bool Database::open(const std::string &path) {
    int result = sqlite3_open_v2(path.c_str(), &this->db,
                                 SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
                                     SQLITE_OPEN_FULLMUTEX,
                                 nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Problem opening Database, path: " + path << std::endl;
        return false;
    }

    return this->create_schema();
}

std::string Database::read_sql_file(const std::string &path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool Database::create_schema() {
    std::string sql = read_sql_file("resources/sql/schema.sql");

    char *err_msg = nullptr;
    int result =
        sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &err_msg);

    if (result != SQLITE_OK) {
        std::cerr << "Problem creating schema: " + std::string(err_msg)
                  << std::endl;
        sqlite3_free(err_msg);
        return false;
    }

    return true;
}