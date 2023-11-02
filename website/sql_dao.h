#ifndef __CALC_SQL_DATABASE_ACCESS_OBJECT_H__
#define __CALC_SQL_DATABASE_ACCESS_OBJECT_H__

#include <iostream>
#include <memory>
#include <sqlite/sqlite3.h>

#include "user.h"
#include "sql_interface.h"
#include "sql_errors.h"
#include "dao.h"

class SqliteDAO : public DatabaseAccessObject {
private:
    std::unique_ptr<sqlite3, SQLDeleter> _db {};

    sqlite3* open_sqlite3_db(const std::string &db_path) noexcept {
        sqlite3 *db;
        sqlite3_open_v2(db_path.c_str(), &db, 0, nullptr);
        return db;
    }

public:
    SqliteDAO() : DatabaseAccessObject() {}
    SqliteDAO(const SqliteDAO &rhs) = delete;
    SqliteDAO(SqliteDAO &&rhs) : DatabaseAccessObject(), _db(std::move(rhs._db)) {}

    void attach_memory() {
        _db = std::unique_ptr<sqlite3, SQLDeleter>(open_sqlite3_db(":memory:"));
    }

    void attach(const std::string &database_path) {
        _db = std::unique_ptr<sqlite3, SQLDeleter>(open_sqlite3_db(database_path));
    }

    void close() {
        _db.reset();
    }

    void run_schema(std::ifstream &schema) {
        if (!schema.is_open()) {
            throw std::runtime_error("Schema not found");
        }

        char *error = nullptr;
        std::string statements((std::istreambuf_iterator<char>(schema)), std::istreambuf_iterator<char>());
        if (sqlite3_exec(_db.get(), statements.c_str(), nullptr, nullptr, &error) != SQLITE_OK) {
            if (error) {
                std::cout << error << '\n';
                sqlite3_free(error);
            }
        }
    }

    // TODO not implemented
    virtual User get_user(int id) override {
        User user;

        return user;
    };

    // TODO not implemented
    virtual User create_user(const std::string &name, const std::string &password) override {
        User user;

        return user;
    };

    // TODO not implemented
    virtual User update_user(int id) override {
        User user;

        return user;
    }

    // TODO not implemented
    virtual void delete_user(int id) override {

    }

    ~SqliteDAO() noexcept {}
};

#endif // __CALC_SQL_DATABASE_ACCESS_OBJECT_H__
