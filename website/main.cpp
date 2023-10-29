#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <sqlite/sqlite3.h>
#include <httplib.h>

#include "dao.h"

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

    void run_server() {
        _server.listen("0.0.0.0", _config["port"]);
    }
public:
    App(const nlohmann::json &config) :_config(config) {
        _dao = std::make_unique<SqliteDAO>(_config["db"], _config["schema"]);

        _server.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
            res.set_content(_inja.render(html_template, _config["example"]), "text/html");
        });
    }

    void run() {
        // std::thread(&App::run_server, this).detach();
        _server.listen("0.0.0.0", _config["port"]);
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
        nlohmann::json config;

        if (argc == 2) {
            config = read_config(argv[1]);
        } else {
            config = read_config("server_config.json");
        }

        auto app = App(config);
        app.run();
    } catch (std::exception e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
