#include <sqlite3.h>
#include <string>

class Database {
  public:
    ~Database() {
        if (db)
            sqlite3_close(this->db);
    }

    bool open(const std::string &path);

  private:
    sqlite3 *db = nullptr;

    bool create_schema();
    std::string read_sql_file(const std::string &path);
};