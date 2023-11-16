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

    // TODO not implemented
    virtual std::optional<User> get_user(int id) noexcept override {
        User user;

        try {
            auto user = _db.select_users("SELECT username, password FROM users WHERE id=%d", id);

            if (user.size() > 0) {
                return user[0];
            }
        } catch (SQLError &e) {

        }

        return std::nullopt;
    };

    // TODO not implemented
    virtual std::optional<int> create_user(const std::string &name, const std::string &password) noexcept override {
        try{
            _db.execute_sql_statement("INSERT INTO users (username, password) VALUES(\"%s\", \"%s\")", name.c_str(), password.c_str());
            auto id = _db.select_int("SELECT id FROM users WHERE username=\"%s\" AND password=\"%s\"", name.c_str(), password.c_str());
            return id;
        } catch (SQLError &e) {
            // TODO later on: report it to the logger
            std::cerr << e.what() << std::endl;
        }

        return std::nullopt;
    };

    // TODO not implemented
    virtual std::optional<User> update_user(int id) noexcept override {
        return std::nullopt;
    }

    // TODO not implemented
    virtual bool delete_user(int id) noexcept override {
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
