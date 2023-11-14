//history service
#ifndef __CALC_HISTORY_SERVICE_HPP__
#define __CALC_HISTORY_SERVICE_HPP__

#include <iostream>
#include <vector>


class HistoryService {
private:
    std::vector<std::string> history; //store history
public:
    HistoryService() {} //initialize history

    void addEntry(const std::string& entry) {
        history.push_back(entry); //add entry
    }

    std::vector<std::string> getHistory() const {
        return history; //get history
    }

    void clearHistory() {
        history.clear();
    }
};

#endif

/*
Input:
Entry to Add: The input for the addEntry() function would be a string representing a calculation or an operation that the user performs on the calculator.
Use Case: This service is designed to maintain a history of calculations or operations performed by the user on the calculator.
Functionality:
addEntry(): Adds a new entry (calculation or operation) to the history.
getHistory(): Retrieves the complete history of entries.
clearHistory(): Clears the entire history.
Example:
Input: Strings representing calculations or operations like "2 + 3", "sin(30)", "sqrt(16)".
Functionality: The service records these inputs and allows the user to retrieve or clear the history as needed.
*/
