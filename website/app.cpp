#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <httplib.h>

#include "app.hpp"

// later on, these will be separate `.html` files loaded in; for now, they're just here.
static const char *user_query =
    "<html>"
    "<body>"
    "  <h1>Hello, {{ username }}!</h1>"
    "</body>"
    "</html>";

static const char *error_response =
    "<html>"
    "<body>"
    "  <h1>{{ status_code }} : {{ reason }}</h1>"
    "</body>"
    "</html>";

App::App(const nlohmann::json &config, ExampleService &example) : _config(config), _example(example) {
    _server.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        get_index(req, res);
    });

    _server.Get("/user", [&](const httplib::Request &req, httplib::Response &res) {
        auto user_id = req.get_param_value("id");

        if (user_id.empty()) {
            get_users_page(req, res);
        } else {
            get_user_at_id(req, res);
        }
    });
}

void App::get_index(const httplib::Request &req, httplib::Response &res) {
    res.set_content("<index goes here>", "text/plain");
}

void App::get_users_page(const httplib::Request &req, httplib::Response &res) {
    res.set_content("<user page goes here>", "text/plain");
}

void App::get_user_at_id(const httplib::Request &req, httplib::Response &res) {
    auto user_id = req.get_param_value("id");

    try {
        auto username = _example.query_username(std::stoi(user_id));

        if (username) {
            nlohmann::json content = {
                { "username", username.value() },
            };

            res.set_content(_inja.render(user_query, content), "text/html");
        } else {
            nlohmann::json content = {
                { "status_code", "404" },
                { "reason", "User with that ID doesn't exist" },
            };
            res.set_content(_inja.render(error_response, content), "text/html");
        }
    } catch (std::exception &e) {
        nlohmann::json content = {
            { "status_code", "500" },
            { "reason", e.what() },
        };
        res.set_content(_inja.render(error_response, content), "text/html");
    }
}

void App::run() {
    _server.listen("0.0.0.0", _config["port"]);
}

void App::run_detach() {
    std::thread(&App::run, this).detach();
}
