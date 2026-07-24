#include <sqlite3.h>
#include <string>
#include <variant>
#include <vector>

using SqlValue = std::variant<std::monostate, int64_t, double, std::string>;

class Database {
  public:
    ~Database() {
        if (db)
            sqlite3_close(this->db);
    }

    bool open(const std::string &path);

    bool op_insert(const std::string &table,
        const std::vector<std::string> &columns,
        const std::vector<SqlValue> &params);

    std::vector<std::vector<SqlValue>> op_select(const std::string &table,
        const std::vector<std::string> &columns,
        const std::string &where_clause,
        const std::vector<SqlValue> &where_params);

    bool op_update(const std::string &table,
        const std::vector<std::string> &columns,
        const std::vector<SqlValue> &params, const std::string &where_clause,
        const std::vector<SqlValue> &where_params = {});

    bool op_delete(const std::string &table, const std::string &where_clause,
        const std::vector<SqlValue> &where_params = {},
        const bool force = false);

  private:
    sqlite3 *db = nullptr;

    bool create_schema();
    std::string read_sql_file(const std::string &path);
    bool execute(
        const std::string &sql, const std::vector<SqlValue> &params = {});
};