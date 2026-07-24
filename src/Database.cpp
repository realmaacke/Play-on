#include "Database.hpp"
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <string>

// Helpers

/**
db.insert("movies", { "m_name", "m_image", "m_group", "m_url" },
{ std::string("Movie A"), std::string("img.jpg"), std::string("Action"),
std::string("http://...") });
*/
bool Database::op_insert(const std::string &table,
    const std::vector<std::string> &columns,
    const std::vector<SqlValue> &params) {

    if (columns.size() != params.size()) {
        std::cerr << "Column count does not match parameter count for table: " +
                         table
                  << std::endl;
        return false;
    }

    std::string column_list;
    std::string placeholders;

    for (size_t i = 0; i < columns.size(); ++i) {
        column_list += columns[i];
        placeholders += "?";

        if (i + 1 < columns.size()) {
            column_list += ", ";
            placeholders += ", ";
        }
    }

    std::string sql = "INSERT INTO " + table + " (" + column_list +
                      ") VALUES (" + placeholders + ");";

    return this->execute(sql, params);
}

/**
std::vector<std::vector<SqlValue>> rows = db.select(
    "movies",
    { "id", "m_name", "m_image", "m_group", "m_url" },
    "m_group = ?",
    { std::string("Action") }
);
*/

std::vector<std::vector<SqlValue>> Database::op_select(const std::string &table,
    const std::vector<std::string> &columns, const std::string &where_clause,
    const std::vector<SqlValue> &where_params) {
    std::vector<std::vector<SqlValue>> rows;

    std::string column_list;
    for (size_t i = 0; i < columns.size(); ++i) {
        column_list += columns[i];
        if (i + 1 < columns.size())
            column_list += ", ";
    }

    std::string sql = "SELECT " + column_list + " FROM " + table;
    if (!where_clause.empty())
        sql += " WHERE " + where_clause;
    sql += ";";

    sqlite3_stmt *stmt = nullptr;
    int result = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Problem preparing statement: " +
                         std::string(sqlite3_errmsg(this->db))
                  << std::endl;
        return rows;
    }

    for (size_t i = 0; i < where_params.size(); ++i) {
        int index = static_cast<int>(i) + 1;

        if (std::holds_alternative<int64_t>(where_params[i])) {
            sqlite3_bind_int64(stmt, index, std::get<int64_t>(where_params[i]));
        } else if (std::holds_alternative<double>(where_params[i])) {
            sqlite3_bind_double(stmt, index, std::get<double>(where_params[i]));
        } else if (std::holds_alternative<std::string>(where_params[i])) {
            sqlite3_bind_text(stmt, index,
                std::get<std::string>(where_params[i]).c_str(), -1,
                SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, index);
        }
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<SqlValue> row;

        for (int col = 0; col < static_cast<int>(columns.size()); ++col) {
            int type = sqlite3_column_type(stmt, col);

            if (type == SQLITE_INTEGER) {
                row.push_back(
                    static_cast<int64_t>(sqlite3_column_int64(stmt, col)));
            } else if (type == SQLITE_FLOAT) {
                row.push_back(sqlite3_column_double(stmt, col));
            } else if (type == SQLITE_TEXT) {
                const unsigned char *text = sqlite3_column_text(stmt, col);
                row.push_back(
                    std::string(reinterpret_cast<const char *>(text)));
            } else {
                row.push_back(std::monostate{});
            }
        }

        rows.push_back(row);
    }

    sqlite3_finalize(stmt);
    return rows;
}

/**
db.update(
    "movies",
    { "m_name", "m_image" },
    { std::string("New Name"), std::string("new_img.jpg") },
    "id = ?",
    { static_cast<int64_t>(5) }
);
*/

bool Database::op_update(const std::string &table,
    const std::vector<std::string> &columns,
    const std::vector<SqlValue> &params, const std::string &where_clause,
    const std::vector<SqlValue> &where_params) {
    if (columns.size() != params.size()) {
        std::cerr << "Column count does not match parameter count for table: " +
                         table
                  << std::endl;
        return false;
    }

    if (where_clause.empty()) {
        std::cerr << "Refusing to update table without a WHERE clause: " + table
                  << std::endl;
        return false;
    }

    std::string set_list;
    for (size_t i = 0; i < columns.size(); ++i) {
        set_list += columns[i] + " = ?";
        if (i + 1 < columns.size())
            set_list += ", ";
    }

    std::string sql =
        "UPDATE " + table + " SET " + set_list + " WHERE " + where_clause + ";";

    std::vector<SqlValue> all_params = params;
    all_params.insert(
        all_params.end(), where_params.begin(), where_params.end());

    return this->execute(sql, all_params);
}

/**
db.remove("movies", "id = ?", { static_cast<int64_t>(5) });
*/
bool Database::op_delete(const std::string &table,
    const std::string &where_clause, const std::vector<SqlValue> &where_params,
    const bool force) {

    if (where_clause.empty() && force == false) {
        std::cerr << "Refusing to delete from table without a WHERE clause: " +
                         table
                  << std::endl;
        return false;
    }

    std::string sql = "DELETE FROM " + table + " WHERE " + where_clause + ";";

    return this->execute(sql, where_params);
}

// End here

bool Database::execute(
    const std::string &sql, const std::vector<SqlValue> &params) {
    sqlite3_stmt *stmt = nullptr;

    int result = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Provlem executing stmt: " +
                         std::string(sqlite3_errmsg(this->db))
                  << std::endl;
        return false;
    }

    for (size_t i = 0; i < params.size(); ++i) {
        int index = static_cast<int>(i) + 1;

        if (std::holds_alternative<int64_t>(params[i])) {
            sqlite3_bind_int64(stmt, index, std::get<int64_t>(params[i]));
        } else if (std::holds_alternative<double>(params[i])) {
            sqlite3_bind_double(stmt, index, std::get<double>(params[i]));
        } else if (std::holds_alternative<std::string>(params[i])) {
            sqlite3_bind_text(stmt, index,
                std::get<std::string>(params[i]).c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, index);
        }
    }

    result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE) {
        std::cerr << "Problem executing statement: " +
                         std::string(sqlite3_errmsg(this->db))
                  << std::endl;
        return false;
    }

    return true;
}

bool Database::open(const std::string &path) {
    int result = sqlite3_open_v2(path.c_str(), &this->db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX,
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