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

App::App(const nlohmann::json &config, AuthService &auth) : _config(config), _auth(auth) {
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

    _server.Get("/create", [&](const httplib::Request &req, httplib::Response &res) {
        auto username = req.get_param_value("name");
        auto password = req.get_param_value("password");

        if (username.empty() || password.empty()) {
            // error page
            get_users_page(req, res);
        } else {
            create_user(req, res);
        }
    });
}

void App::get_index(const httplib::Request &req, httplib::Response &res) {
    res.set_content("<index goes here>", "text/plain");
}

void App::get_users_page(const httplib::Request &req, httplib::Response &res) {
    res.set_content("<user page goes here>", "text/plain");
}

void App::run() {
    _server.listen("0.0.0.0", _config["port"]);
}

void App::run_detach() {
    std::thread(&App::run, this).detach();
}
