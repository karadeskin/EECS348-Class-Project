//scripting service
#ifndef __CALC_SCRIPTING_SERVICE_HPP__
#define __CALC_SCRIPTING_SERVICE_HPP__

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

class ScriptingService {
private:
    std::vector<std::function<double()>> scripts; // Store user-defined scripts

public:
    ScriptingService() {}

    //new script to the service
    void addScript(const std::function<double()>& script) {
        scripts.push_back(script);
    }

    //execute all scripts and return results
    std::vector<double> executeScripts() const {
        std::vector<double> results;
        for (const auto& script : scripts) {
            try {
                double result = script(); //execute the script
                results.push_back(result);
            } catch (const std::exception& e) {
                //handle exceptions if the script encounters an error
                std::cerr << "Script execution error: " << e.what() << std::endl;
            }
        }
        return results;
    }

    //clear all scripts
    void clearScripts() {
        scripts.clear();
    }
};

#endif

/*
Input:
Script: A user-defined function or operation that performs a calculation using the calculator's functionalities.
Use Case: Allows users to automate and customize calculations by creating custom scripts.
Functionality:
addScript(): Adds a user-defined script (function) that can perform calculations using the calculator's functionalities.
executeScripts(): Executes all added scripts and returns their results.
clearScripts(): Clears all user-defined scripts.
Example:
Input: Functions or operations utilizing the calculator's capabilities, such as add, subtract, multiply, divide, etc., in custom user-defined functions.
Functionality: Users create scripts that use the calculator's functions to perform complex or specific calculations automatically.
*/
