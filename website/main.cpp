#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <sqlite/sqlite3.h>
#include <httplib.h>

#include "sql_dao.h"

static const char *html_template =
    "<html>\n"
    "<body>\n"
    "    <h1>{{ text }}<code>&#8212;</code>the date is {{ date }}!</h1>\n"
    "    <h2>my favorite animals:</h2>\n"
    "    <ul>\n"
    "    {% for animal in animals %}\n"
    "        <li>{{ animal }}</li>\n"
    "    {% endfor %}\n"
    "    </ul>\n"
    "</body>\n"
    "</html>";

class App {
private:
    nlohmann::json _config {};
    std::unique_ptr<DatabaseAccessObject> _dao {};
    httplib::Server _server {};
    inja::Environment _inja {};
public:
    App(const nlohmann::json &config, std::unique_ptr<DatabaseAccessObject> &&dao) : _config(config), _dao(std::move(dao)) {
        _server.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
            res.set_content(_inja.render(html_template, _config["example"]), "text/html");
        });
    }

    // listen for connections and respond.
    // caution: this blocks the thread it's called on
    void run() {
        _server.listen("0.0.0.0", _config["port"]);
    }

    // listen in a separate thread as not to block the main thread
    void run_detach() {
        std::thread(&App::run, this).detach();
    }
};

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
        std::ifstream schema(config["schema"].get<std::string>());
        auto sql_dao = std::make_unique<SqliteDAO>();
        sql_dao->attach(config["db"]);
        sql_dao->run_schema(schema);

        // begin running the app
        auto app = App(config, std::move(sql_dao));
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
