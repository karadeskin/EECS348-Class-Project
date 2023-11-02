#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <sqlite/sqlite3.h>
#include <httplib.h>

#include "app.h"
#include "sql_dao.h"

nlohmann::json read_config(const std::string &path) {
    std::ifstream f(path);

    if (!f.is_open()) {
        throw std::runtime_error(std::string { "Failed to open " + path });
    }

    return nlohmann::json::parse(f);
}

int main(int argc, char *argv[]) {
    try {
        // read in our config file
        nlohmann::json config;

        if (argc == 2) {
            config = read_config(argv[1]);
        } else {
            config = read_config("server_config.json");
        }

        // set up the SQLite DAO
        std::ifstream schema_loc(config["schema"].get<std::string>());
        auto sql_dao = std::make_unique<SqliteDAO>();
        sql_dao->attach(config["db"]);
        sql_dao->run_schema(schema_loc);

        // begin running the app
        auto app = App(config);
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
