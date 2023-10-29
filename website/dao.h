#ifndef __CALC_DAO_H__
#define __CALC_DAO_H__

#include <fstream>
#include <memory>
#include <streambuf>
#include <string>
#include <string_view>

#include <sqlite/sqlite3.h>

struct SQLDestructor {
    void operator()(sqlite3 *db) noexcept { sqlite3_close_v2(db); }
    void operator()(sqlite3_stmt *stmt) noexcept { sqlite3_finalize(stmt); }
};

class DatabaseAccessObject {
public:
    DatabaseAccessObject() {}
    virtual ~DatabaseAccessObject() noexcept {}
};

class SqliteDAO : public DatabaseAccessObject {
private:
    std::unique_ptr<sqlite3, SQLDestructor> _db {};

    sqlite3 *open_sqlite3_db(const std::string_view db_path) noexcept {
        sqlite3 *db;
        sqlite3_open_v2(db_path.cbegin(), &db, 0, nullptr);
        return db;
    }

    std::string read_file(const std::string_view path) {
        std::ifstream t(path);
        if (t.is_open()) {
            std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
            return str;
        }

        return "";
    }
public:
    SqliteDAO(const std::string &db_path, const std::string &schema)
        : DatabaseAccessObject() {
        if (db_path.empty()) {
            _db = std::unique_ptr<sqlite3, SQLDestructor>(open_sqlite3_db(":memory:"));
        } else {
            _db = std::unique_ptr<sqlite3, SQLDestructor>(open_sqlite3_db(db_path));
        }

        std::string statements = read_file(schema);
        if (!statements.empty()) {
            char *error = nullptr;
            if (sqlite3_exec(_db.get(), statements.c_str(), nullptr, nullptr, &error) != SQLITE_OK) {
                if (error) {
                    std::cout << error << '\n';
                    sqlite3_free(error);
                }
            }
        } else {
            std::cout << "failed to read\n";
        }
    }

    ~SqliteDAO() noexcept {}
};

#endif // __CALC_DAO_H__
