#ifndef __CALC_SQL_USER_DAO_HPP__
#define __CALC_SQL_USER_DAO_HPP__

#include <cstdio>
#include <iostream>
#include <memory>
#include <optional>

#include <sqlite/sqlite3.h>
#include <nlohmann/json.hpp>

#include "user.hpp"
#include "sql_interface.hpp"
#include "dao.hpp"

class SQLUserDatabaseAccessObject : public UserDatabaseAccessObject {
private:
    SQLiteDatabase _db;

    void run_schema(std::ifstream &schema) {
        if (!schema.is_open()) {
            throw std::runtime_error("Schema not found");
        }

        char *error = nullptr;
        std::string statements((std::istreambuf_iterator<char>(schema)), std::istreambuf_iterator<char>());
        _db.execute_sql_statement(statements.c_str());
    }

public:
    SQLUserDatabaseAccessObject(const nlohmann::json &config) : UserDatabaseAccessObject(config) {
        if (config.at("db").is_string()) {
            _db.attach(config["db"]);
        } else {
            _db.attach_memory();
        }

        if (config.at("schema").is_string()) {
            std::ifstream schema;
            schema.open(config["schema"].get<std::string>());
            run_schema(schema);
        } else {
            throw std::runtime_error("Database schema not found");
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
