#include <iostream>
#include <string>
#include <unordered_map>
#include <inja/inja.hpp>

class Templating {
private:
    std::unordered_map<std::string, std::string> templates;

public:
    void load(const std::string &fileName) {
        
        std::string fileContent = ""; // load file content via string 

        // store in memory
        templates[fileName] = fileContent;
    }

    std::string render(const std::string &fileName, const nlohmann::json &data) {
        // check if the template exists
        if (templates.find(fileName) == templates.end()) {
            return "template not found";
        }

        // template content
        std::string templateContent = templates[fileName];

        inja::Environment env;
        env.setExpression("<%", "%>"); 
        try {
            return env.render(templateContent, data);
        } catch (const inja::RenderError &e) {
            return "render error: " + std::string(e.what());
        }
    }
};
