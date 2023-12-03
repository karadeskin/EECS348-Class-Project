#ifndef __CALC_APP_HPP__
#define __CALC_APP_HPP__

#include <nlohmann/json.hpp>
#include <httplib.h>

#include <Interface.h>

class App {
private:
    Interface _calc;
    httplib::Server _server {};
    nlohmann::json _config {};
public:
    // links together all of the other pieces of the web app
    App(const nlohmann::json &config);

    // listen for connections and respond.
    // caution: this blocks the thread it's called on
    void run();

    // listen in a separate thread as not to block the main thread
    void run_detach();
};

#endif // __CALC_APP_HPP__
