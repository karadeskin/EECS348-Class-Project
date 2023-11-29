#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <sqlite/sqlite3.h>
#include <httplib.h>

#include "html_template.hpp"
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

        // set up inja templates
        auto template_engine = Templating();
        for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            if (std::filesystem::is_regular_file(entry) && entry.path().extension() == ".html") {
                template_engine.load(entry.path().filename());
            }
        }

        // instantiate an example service
        AuthService auth(user_dao);

        // pass the service to our app and begin running
        auto app = App(config, template_engine, auth);
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    } catch (SQLError &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
