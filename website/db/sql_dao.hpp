#ifndef __CALC_SQL_DAO_HPP__
#define __CALC_SQL_DAO_HPP__

#include <fstream>
#include <string>

#include "sql_interface.hpp"

class SQLDatabaseAccessObject {
protected:
    SQLiteDatabase _db;

    void run_schema(std::ifstream &schema) {
        if (!schema.is_open()) {
            throw std::runtime_error("Schema not found");
        }

        char *error = nullptr;
        std::string statements((std::istreambuf_iterator<char>(schema)), std::istreambuf_iterator<char>());
        _db.execute_sql_statement(statements.c_str());
    }

    SQLDatabaseAccessObject(const nlohmann::json &config) {
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
};

#endif // __CALC_SQL_DAO_HPP__