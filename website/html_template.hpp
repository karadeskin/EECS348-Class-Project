#include <iostream>
#include <string>
#include <unordered_map>
#include <inja/inja.hpp>

class Templating {
private:
    std::unordered_map<std::string, std::string> templates;
    inja::Environment env;

public:
    void load(const std::string &fileName) {
    std::ifstream fileStream(fileName); 
    if (fileStream) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        // store in memory
        templates[fileName] = fileContent;
        fileStream.close(); // close file
    } else {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

    std::string render(const std::string &fileName, const nlohmann::json &data) {
        // check if the template exists
        if (templates.find(fileName) == templates.end()) {
            return "template not found";
        }

        // template content
        std::string templateContent = templates[fileName];

        env.setExpression("<%", "%>"); 
        try {
            return env.render(templateContent, data);
        } catch (const inja::RenderError &e) {
            return "render error: " + std::string(e.what());
        }
    }
};


