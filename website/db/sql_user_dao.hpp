#ifndef __CALC_SQL_USER_DAO_HPP__
#define __CALC_SQL_USER_DAO_HPP__

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>

#include <sqlite/sqlite3.h>
#include <nlohmann/json.hpp>

#include "sql_dao.hpp"
#include "user_dao.hpp"

class SQLUserDatabaseAccessObject : public UserDatabaseAccessObject, public SQLDatabaseAccessObject {
public:
    SQLUserDatabaseAccessObject(const nlohmann::json &config)
        : UserDatabaseAccessObject(), SQLDatabaseAccessObject(config) {}

    virtual std::optional<User> get_user(int id) override {
        User user;

        auto query = _db.prepare_sql_statement("SELECT username, password FROM users WHERE id=%d", id);
        int rc = sqlite3_step(query.get());

        if (rc == SQLITE_ROW) {
            user._username = std::string(reinterpret_cast<const char*>(sqlite3_column_text(query.get(), 0)));
            user._password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(query.get(), 1)));
        }

        if (rc != SQLITE_DONE) {
            if (rc == SQLITE_DONE) {
                return std::nullopt;
            } else if (rc == SQLITE_BUSY) {
                throw SQLBusyError(_db.handle(), query);
            } else if (rc == SQLITE_CONSTRAINT) {
                throw SQLConstraintError(_db.handle(), query);
            }

            throw SQLGenericError(_db.handle(), query);
        }

        return user;
    };

    virtual bool user_exists(const std::string &name) override {
        try {
            auto query = _db.prepare_sql_statement("SELECT * FROM users WHERE username=\"%s\"", name.c_str());
            return sqlite3_step(query.get()) == SQLITE_ROW;
        } catch (SQLError &e) {
            std::cerr << e.what() << std::endl;
        }

        return false;
    }

    virtual bool create_user(const std::string &name, const std::string &password) override {
        try{
            _db.execute_sql_statement("INSERT INTO users (username, password) VALUES(\"%s\", \"%s\")", name.c_str(), password.c_str());
            return true;
        } catch (SQLError &e) {
            // TODO later on: report it to the logger
            std::cerr << e.what() << std::endl;
            return false;
        }
    };

    // TODO not implemented
    virtual std::optional<User> update_user(int id) override {
        return std::nullopt;
    }

    virtual std::optional<std::string> get_password(const std::string &name) override {
        auto query = _db.prepare_sql_statement("SELECT password FROM users WHERE username=%s", name.c_str());
        int rc = sqlite3_step(query.get());
        std::string password {};

        if (rc == SQLITE_ROW) {
            password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(query.get(), 1)));
            return password;
        }

        return std::nullopt;
    }

    // TODO not implemented
    virtual bool delete_user(int id) override {
        try {
            _db.execute_sql_statement(R"(DELETE FROM users WHERE id=%d)", id);
            return true;
        } catch (SQLError &e) {
            // TODO later on: report it to the logger
            std::cerr << e.what() << std::endl;
        }

        return false;
    }

    ~SQLUserDatabaseAccessObject() noexcept {}
};

#endif // __CALC_SQL_USER_DAO_HPP__
