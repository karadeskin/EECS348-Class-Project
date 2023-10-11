#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>
#include <sqlite/sqlite3.h>
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

void run_server(httplib::Server *server) {
    server->listen("0.0.0.0", 3000);
}

int main(int argc, char *argv[]) {
    nlohmann::json my_json;
    my_json["text"] = "hello, world!";
    my_json["date"] = "10-11-23";
    my_json["animals"] = {
        "cats", "dogs", "bats", "rats", "goats", "sheep"
    };

    inja::Environment env;
    std::cout << env.render(html_template, my_json) << '\n';

    sqlite3 *db = nullptr;
    sqlite3_open_v2(":memory:", &db, 0, nullptr);

    sqlite3_close_v2(db);

    httplib::Server server;

    server.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        res.set_content(env.render(html_template, my_json), "text/html");
    });

    // listen blocks so spawn a thread just for the server
    std::thread(run_server, &server).detach();

    // we don't do anything else so just sleep
    using namespace std::chrono_literals;
    for (;;) {
        std::this_thread::sleep_for(1s);
    }

    return 0;
}
