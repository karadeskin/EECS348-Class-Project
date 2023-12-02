#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <httplib.h>

#include <Interface.h>

#include "app.hpp"

App::App(const nlohmann::json &config) : _config(config) {
    _server.set_mount_point("/", ".");

    _server.Post("/", [&](const httplib::Request &req, httplib::Response &res) {
        nlohmann::json expression = nlohmann::json::parse(req.body);
        auto result = _calc.solve_equation(expression["expression"]);
        std::cout << "POST: /\n" << req.body << '\n';
        res.set_content(result, "text/plain");
    });
}

void App::run() {
    _server.listen(_config["ip"], _config["port"]);
}

void App::run_detach() {
    std::thread(&App::run, this).detach();
}
