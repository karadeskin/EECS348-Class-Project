#ifndef __CALC_HTML_TEMPLATING_HPP__
#define __CALC_HTML_TEMPLATING_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <inja/inja.hpp>

class Templating {
private:
    std::unordered_map<std::string, inja::Template> templates;
    inja::Environment env;
    std::unordered_map<std::string, std::string> html;

public:
    void load(const std::string &fileName) {
        std::ifstream fileStream(fileName);
        if (fileStream) {
            std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
            // parse the file content and store in memory
            inja::Template contentTemplate = env.parse(fileContent);
            html[fileName] = fileContent;
            fileStream.close(); // close file
        } else {
            std::cerr << "Unable to open file: " << fileName << std::endl;
        }
    }

    std::string render(const std::string &fileName, const nlohmann::json &data) {
        // check if the template exists
        if (html.find(fileName) == html.end()) {
            return "Template not found";
        }

        // get the template from memory
        inja::Template& templateRef = templates[fileName];

        try {
            // render the template with the provided data
            return env.render(html[fileName], data);
        } catch (const inja::RenderError &e) {
            return "Render error: " + std::string(e.what());
        }
    }

        std::string render(const std::string &fileName) {
        // check if the template exists
        if (html.find(fileName) == html.end()) {
            return "Template not found";
        }

        // get the template from memory
        inja::Template& templateRef = templates[fileName];

        try {
            // render the template with the provided data
            return env.render(html[fileName], nlohmann::json());
        } catch (const inja::RenderError &e) {
            return "Render error: " + std::string(e.what());
        }
    }
};

#endif // __CALC_HTML_TEMPLATING_HPP__