#include <iostream>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>

static const char *html_template =
    "<html>\n"
    "<body>\n"
    "    <h1>{{ text }}, the date is {{ date }}!</h1>\n"
    "    <h2>my favorite animals:</h2>\n"
    "    <ul>\n"
    "    {\% for animal in animals \%}\n"
    "        <li>{{ animal }}</li>\n"
    "    {\% endfor \%}\n"
    "    </ul>\n"
    "</body>\n"
    "</html>";

int main(int argc, char *argv[]) {
    nlohmann::json my_json;
    my_json["text"] = "hello, world!";
    my_json["date"] = "10-9-23";
    my_json["animals"] = {
        "cats", "dogs", "bats", "rats", "goats", "sheep"
    };

    inja::Environment env;
    std::cout << env.render(html_template, my_json) << '\n';

    return 0;
}
