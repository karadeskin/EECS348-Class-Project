#include <iostream>
#include <vector>
#include <iterator>
#include <string>

template <typename T>
void vec_print(const std::vector<T>& container) {   //Print vector, entry by entry
    for (const T equation : container)              //Found online, modified to generic type
        std::cout << equation << ' ';
    std::cout << std::endl;
}

bool char_is_num(const char c) {        //Return true if character c is a numeral, false if not
    if ((c == '0') or (c == '1') or (c == '2') or (c == '3') or (c == '4') or (c == '5') or (c == '6') or (c == '7') or (c == '8') or (c == '9')) {
        return true;
    }
    else {
        return false;
    }
}


int main() {

    std::string equ_str;                    //Initialize equation variables, and take input of equation
    std::cout << "Enter equation: ";
    std::cin >> equ_str;
    std::vector<std::string> equ_vec;

    std::string num_str;                    //Variable to hold numeric characters, to combine multiple numeric characters into one number
    int equ_str_index = 0;                  //Variable to track which character in the equation we are one
    for (char c : equ_str) {                //Iterate through the equation, one character at a time

        switch (c) {
        case '0':                           //If the current character is a 0;
            if (equ_str_index == 0) {       //If the current character is the first in the string, or if the preceding character is not a number,
                num_str = "0";              //the current character is the first character in a number-string, so set num_str equal to the character, typed as a string
            }
            else if (char_is_num(equ_str[equ_str_index-1]) == false) {
                num_str = "0";
            }
            else {                          //If the current character is not the first in the string, and is preceded by a number,
                num_str.append("0");        //it is part of an existing number-string, so append it to the existing num_str
            }

            if (equ_str_index == (equ_str.length() - 1)) {                  //If the current character is the last in the equation,
                equ_vec.push_back(num_str);                                 //or the next character is not a number,
            }                                                               //the current character is the last character in the number-string,
            else if (char_is_num(equ_str[equ_str_index+1]) == false) {      //so we append num_str to the end of the equation vector.
                equ_vec.push_back(num_str);                                 //If it isn't the last character in the number-string, don't do anything
            }
            break;
        case '1':                               //Repeat above steps for each numeral, 0 - 9
            if (equ_str_index == 0) {
                num_str = "1";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "1";
            }
            else {
                num_str.append("1");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '2':
            if (equ_str_index == 0) {
                num_str = "2";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "2";
            }
            else {
                num_str.append("2");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '3':
            if (equ_str_index == 0) {
                num_str = "3";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "3";
            }
            else {
                num_str.append("3");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '4':
            if (equ_str_index == 0) {
                num_str = "4";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "4";
            }
            else {
                num_str.append("4");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '5':
            if (equ_str_index == 0) {
                num_str = "5";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "5";
            }
            else {
                num_str.append("5");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '6':
            if (equ_str_index == 0) {
                num_str = "6";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "6";
            }
            else {
                num_str.append("6");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '7':
            if (equ_str_index == 0) {
                num_str = "7";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "7";
            }
            else {
                num_str.append("7");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '8':
            if (equ_str_index == 0) {
                num_str = "8";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "8";
            }
            else {
                num_str.append("8");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '9':
            if (equ_str_index == 0) {
                num_str = "9";
            }
            else if (char_is_num(equ_str[equ_str_index - 1]) == false) {
                num_str = "9";
            }
            else {
                num_str.append("9");
            }

            if (equ_str_index == (equ_str.length() - 1)) {
                equ_vec.push_back(num_str);
            }
            else if (char_is_num(equ_str[equ_str_index + 1]) == false) {
                equ_vec.push_back(num_str);
            }
            break;
        case '+':                                       //If the current character is a +,
            equ_vec.push_back("+");                     //append it directly to the equation vector
            break;
        default:                                        //If the current character is anything else,
            std::cout << "ERROR: Undefined character!"; //print error message - needs actual error handling process?
            break;
        }
        equ_str_index++;        //Increment the character index tracker

    }
    vec_print<std::string>(equ_vec);        //Print equation vector for verification purposes - remove before final submission
    std::cout << "\n\n";

                                            //Start of actual calculator
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int equ_vec_index = 0;              //Variable to track which entry in the equation we are on
        int result;                         //Variable to store the result
        for (std::string str : equ_vec) {   //Iterate over the entries in the equation
            if (str == "+") {               //If the current entry is a +,
                found_operator = true;      //Update operator tracker
                result = std::stoi(equ_vec[(equ_vec_index - 1)]) + std::stoi(equ_vec[(equ_vec_index + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                equ_vec.erase(equ_vec.begin() + (equ_vec_index - 1));           //Remove the left operand from the equation vector
                equ_vec.erase(equ_vec.begin() + (equ_vec_index - 1));           //Remove the operator from the equation vector
                equ_vec.erase(equ_vec.begin() + (equ_vec_index - 1));           //Remove the right operand from the equation vector
                equ_vec.insert(equ_vec.begin() + (equ_vec_index - 1), std::to_string(result));  //Convert the result to a string, and insert it where the left operand was
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            equ_vec_index++;    //Increment the entry index tracker
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
    vec_print<std::string>(equ_vec);    //Print final vector, should contain only a single number-string, the final result of the calculations

    return 0;
}
