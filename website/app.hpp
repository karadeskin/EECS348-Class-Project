#ifndef __CALC_APP_HPP__
#define __CALC_APP_HPP__

#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <httplib.h>

#include "services/example_service.hpp"

class App {
private:
    nlohmann::json _config {};
    httplib::Server _server {};
    inja::Environment _inja {};
    ExampleService &_example;

    // responds to the endpoint: /
    void get_index(const httplib::Request &req, httplib::Response &res);

    // responds to the endpoint: /user
    void get_users_page(const httplib::Request &req, httplib::Response &res);

    // responds to the endpoint: /user?id=`id`
    void get_user_at_id(const httplib::Request &req, httplib::Response &res);
public:
    // links together all of the other pieces of the web app
    App(const nlohmann::json &config, ExampleService &example);

    // listen for connections and respond.
    // caution: this blocks the thread it's called on
    void run();

    // listen in a separate thread as not to block the main thread
    void run_detach();
};

#endif // __CALC_APP_HPP__
