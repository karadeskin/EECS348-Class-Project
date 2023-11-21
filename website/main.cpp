#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <sqlite/sqlite3.h>
#include <httplib.h>

#include "services/auth_service.hpp"
#include "app.hpp"
#include "db/sql_user_dao.hpp"
#include "db/sql_history_dao.hpp"
#include "db/sql_script_dao.hpp"

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

        // set up the sqlite3 user DAOs
        auto user_dao = std::make_shared<SQLUserDatabaseAccessObject>(config);
        auto history_dao = std::make_shared<SQLHistoryDatabaseAccessObject>(config);
        auto script_dao = std::make_shared<SQLScriptDatabaseAccessObject>(config);

        // instantiate an example service
        ExampleService example(user_dao);

        // pass the service to our app and begin running
        auto app = App(config, example);
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    } catch (SQLError &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
