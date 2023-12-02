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

App::App(const nlohmann::json &config, Templating &inja, AuthService &auth) : _config(config), _inja(inja), _auth(auth) {
    _server.set_mount_point("/", ".");
    _server.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        std::cout << "GET: /\n";
        get_index(req, res);
    });

    _server.Post("/", [&](const httplib::Request &req, httplib::Response &res) {
        std::cout << "POST: /\n" << req.body << '\n';
        res.set_content("bro idk...", "text/plain");
    });

    _server.Get("/error", [&](const httplib::Request &req, httplib::Response &res) {
        std::cout << "GET: /error\n";
        get_error(req, res);
    });

    _server.Get("/user", [&](const httplib::Request &req, httplib::Response &res) {
        std::cout << "GET: /user\n";
        auto user_name = req.get_param_value("username");

        if (user_name.empty()) {
            // error page
            res.set_redirect("/error", 400);
        } else {
            get_users_page(req, res);
        }
    });

    _server.Get("/sign-up", [&](const httplib::Request &req, httplib::Response &res) {
        std::cout << "GET: /sign-up\n";
        get_signup(req, res);
    });

    _server.Post("/sign-up", [&](const httplib::Request &req, httplib::Response &res) {
        std::cout << "POST: /sign-up\n";
        auto username = req.get_param_value("name");
        auto password = req.get_param_value("password");
 
        if (username.empty() || password.empty()) {
            // error page
            std::cout << "/sign-up: empty params\n";
            res.set_redirect("/error", 400);
        } else {
            if (_auth.createAccount(username, password)) {
                std::cout << "/sign-up: made acc\n";
            } else {
                std::cout << "/sign-up: failed to make acc\n";
            }
            res.set_redirect("/", 200);
        }
    });
}

void App::get_index(const httplib::Request &req, httplib::Response &res) {
    res.set_content(_inja.render("index.html"), "text/html");
}

void App::get_error(const httplib::Request &req, httplib::Response &res) {
    res.set_content("<error>", "test/plain");
}

void App::get_users_page(const httplib::Request &req, httplib::Response &res) {
    res.set_content("<user page goes here>", "text/plain");
}

void App::get_signup(const httplib::Request &req, httplib::Response &res) {
    res.set_redirect("/", 200);
}

void App::create_user(const httplib::Request &req, httplib::Response &res) {
    res.set_redirect("/", 200);
}

void App::run() {
    _server.listen("0.0.0.0", _config["port"]);
}

void App::run_detach() {
    std::thread(&App::run, this).detach();
}
