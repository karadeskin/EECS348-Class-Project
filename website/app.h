#ifndef __CALC_APP_H__
#define __CALC_APP_H__

#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <httplib.h>

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
    httplib::Server _server {};
    inja::Environment _inja {};
public:
    App(const nlohmann::json &config) : _config(config) {
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

#endif // __CALC_APP_H__