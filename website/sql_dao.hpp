#ifndef __CALC_SQL_USER_DAO_HPP__
#define __CALC_SQL_USER_DAO_HPP__

#include <iostream>
#include <memory>
#include <optional>

#include <sqlite/sqlite3.h>

#include "user.hpp"
#include "sql_interface.hpp"
#include "sql_errors.hpp"
#include "dao.hpp"

class SQLUserDatabaseAccessObject : public UserDatabaseAccessObject {
private:
    std::unique_ptr<sqlite3, SQLDeleter> _db {};

    sqlite3* open_sqlite3_db(const std::string &db_path) noexcept {
        sqlite3 *db;
        sqlite3_open_v2(db_path.c_str(), &db, 0, nullptr);
        return db;
    }

public:
    SQLUserDatabaseAccessObject() : UserDatabaseAccessObject() {}

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
    virtual std::optional<User> get_user(int id) noexcept override {
        return std::nullopt;
    };

    // TODO not implemented
    virtual std::optional<User> create_user(const std::string &name, const std::string &password) noexcept override {
        return std::nullopt;
    };

    // TODO not implemented
    virtual std::optional<User> update_user(int id) noexcept override {
        return std::nullopt;
    }

    // TODO not implemented
    virtual bool delete_user(int id) noexcept override {
        return false;
    }

    ~SQLUserDatabaseAccessObject() noexcept {}
};

#endif // __CALC_SQL_USER_DAO_HPP__
