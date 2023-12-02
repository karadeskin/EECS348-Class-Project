#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <sqlite/sqlite3.h>
#include <httplib.h>

#include "app.hpp"

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

        // pass the service to our app and begin running
        auto app = App(config);
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
