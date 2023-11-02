#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <format>
using namespace std;

template <typename T>
void vec_print(const vector<T> &container) {   //Print vector, entry by entry
    for (const T& object : container)              //Found online, modified to generic type
        cout << object << ' ';
    cout << endl;
}

bool char_is_num(const char c) {        //Return true if character c is a numeral, false if not
    if ((c >= '0') && (c <= '9')) {
        return true;
    }
    else {
        return false;
    }
}

vector<string> str_to_strvec(string &equ_str) {
    string num_str;                                    //Variable to hold numeric characters, to combine multiple numerals into a single number-string
    vector<string> equ_vec;                       //Variable to hold vector version of equation string
    for (int i = 0; i < equ_str.length(); i++) {              //Iterate i over indices in equ_str vector
        string character = { equ_str[i] };               //Define character variable as a string, and assign the string conversion of the entry of equ_str at index i

        if (char_is_num(equ_str[i])) {                          //Check if the character in equ_str at index i is a number.
            num_str.append(character);
            if (i == (equ_str.length() - 1)) {                  //If i is at the end of the vector,
                equ_vec.push_back(num_str);                     //or the next character is not a number,
                num_str = "";       //Reset num_str
            }                                                   //the current character is the last character in its number-string.
            else if (char_is_num(equ_str[i + 1]) == false) {    //So, num_str is added to the end of the equ_vec vector
                equ_vec.push_back(num_str);
                num_str = "";       //Reset num_str
            }                                                   //If not, nothing is done.
        }

        else if (character == "+" || character == "*" || character == "/" || character == "%" || character == "^") {        //If the current character is a +, *, /, %, ^
            if (i == 0 || i == (equ_str.length() - 1)) {        //If character is the first or last charcter, throw an error
                throw(runtime_error("Operator is missing an operand."));
            }
            else if (char_is_num(equ_str[i - 1]) == true && char_is_num(equ_str[i + 1]) == true) { //character is preceded and followed by a number
                equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
            }
            else if (char_is_num(equ_str[i - 1]) == true && equ_str[i + 1] == '-') { //character is preceded by a number and followed by a negative sign
                equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
            }
            else {                                              //character not preceded and followed by a number,
                throw(runtime_error("Operator is missing an operand."));   //throw an error

            }
        }

        else if (character == "-") {                            //Current character is a -
            if (i == 0) {                                       //Character is first in string so character is a negative sign
                if (i == equ_str.length() - 1) {                //Character is at end of string
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
                else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                    num_str = character;                        //set num_str equal to the character
                }
                else {                                          //Negative sign not followed by number
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
            }
            else if (char_is_num(equ_str[i - 1]) == false) {    //Proceding character is not a number so character is a negative sign
                if (i == equ_str.length() - 1) {                //Character is at end of string
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
                else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                    num_str = character;                        //set num_str equal to the character
                }
                else {                                          //Negative sign not followed by number
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
            }
            else if (i != equ_str.length() - 1) {               //Character is a minus operator, that is not the last character in the string
                if (char_is_num(equ_str[i + 1]) == true || equ_str[i + 1] == '-') {      //Following character is a number or negative sign
                    equ_vec.push_back(character);               //add the string version to the end of equ_vec.
                }
                else {
                    throw(runtime_error("Minus operator is missing an operand."));    //Throw error
                }
            }
            else {
                throw(runtime_error("Minus operator is missing an operand."));    //Throw error
            }
        }

        else {                                                  //If an unrecognized character is detected, print error message and abort loop
            throw(runtime_error("Unrecognized character in input."));   //If character not coded for, throw error
        }
    }
    return equ_vec;     //Return created vector
}

void replace_sub_equ(vector<string> &equ_vec, int first_index, int length, int result) {
    for (int i = first_index; i <= first_index + (length-1); i++) {     //Remove sub-equation from equation vector
        equ_vec.erase(equ_vec.begin() + first_index);
    }
    equ_vec.insert(equ_vec.begin() + first_index, to_string(result));  //Convert the result to a string, and insert it where the left operand was
}



void add_sub_calc(vector<string> &equ_vec) {
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int result;                         //Variable to store the result
        for (int i = 0; i < equ_vec.size(); i++) {   //Iterate over indices in equ_vec
            if (equ_vec[i] == "+") {               //If the entry at current index is a +,
                found_operator = true;      //Update operator tracker
                result = stoi(equ_vec[(i - 1)]) + stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, result);         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            else if (equ_vec[i] == "-") {               //If the entry at current index is a -,
                found_operator = true;      //Update operator tracker
                result = stoi(equ_vec[(i - 1)]) - stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, result);         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
}

void mult_div_mod_calc(vector<string>& equ_vec) {
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int result;                         //Variable to store the result
        for (int i = 0; i < equ_vec.size(); i++) {   //Iterate over indices in equ_vec
            if (equ_vec[i] == "*") {               //If the entry at current index is a *,
                found_operator = true;      //Update operator tracker
                result = stoi(equ_vec[(i - 1)]) * stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, result);         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            else if (equ_vec[i] == "/") {               //If the entry at current index is a /,
                if (stoi(equ_vec[i + 1]) == 0) {
                    throw(runtime_error("Cannot divide by zero."));
                }
                found_operator = true;      //Update operator tracker
                result = stoi(equ_vec[(i - 1)]) / stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, result);         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            else if (equ_vec[i] == "%") {               //If the entry at current index is a %,
                found_operator = true;      //Update operator tracker
                result = stoi(equ_vec[(i - 1)]) % stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, result);         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
    add_sub_calc(equ_vec);              //Call addition and subtraction function
}

void exp_calc(vector<string>& equ_vec) {
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int result;                         //Variable to store the result
        for (int i = 0; i < equ_vec.size(); i++) {   //Iterate over indices in equ_vec
            if (equ_vec[i] == "^") {               //If the entry at current index is a ^,
                found_operator = true;      //Update operator tracker
                result = pow(stoi(equ_vec[(i - 1)]), stoi(equ_vec[(i + 1)]));   //Convert operands to integers, pass to power function, assign results to result
                replace_sub_equ(equ_vec, i - 1, 3, result);         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
    mult_div_mod_calc(equ_vec);         //Call multiplication, division, and modulo function
}

string remove_spaces(string &old_str) {
    string new_str = "";                            //New string to hold result
    string temp_char_str = "a";                     //Temporary variable to hold string conversion of characters
    for (int i = 0; i < old_str.length(); i++) {    //Iterate every index in string
        if (old_str[i] == ' ') {                    //If the current character is a space
            if (i > 0 && i < old_str.length() - 1) {    //If the current character is not the first or last character
                if (char_is_num(old_str[i - 1]) == true && char_is_num(old_str[i + 1]) == true) {   //If the current character is preceded and followed by numbers
                    throw(runtime_error("Missing operator."));  //Current character is a space surrounded by numbers. Throw error
                }
            }
        }
        else {                                      //Character is not a space
            temp_char_str[0] = old_str[i];          //String conversion of character: assign character to first (and only) index in string
            new_str.append(temp_char_str);          //Append converted character to new string
        }
    }
    return new_str;                                 //Return new string
}

int main() {

    string equ_str;                    //Initialize equation variables, and take input of equation
    cout << "Enter equation: ";
    getline(cin, equ_str);
    vector<string> equ_vec;

    try {
        equ_str = remove_spaces(equ_str);
        equ_vec = str_to_strvec(equ_str);       //Call function to convert string to vector, assign result to equ_vec
        cout << "After function call: " << equ_str << '\n';
        vec_print<string>(equ_vec);             //Print equation vector for verification purposes - remove before final submission
        cout << "\n\n";

        exp_calc(equ_vec);                      //Start calculation function sequence

        vec_print<string>(equ_vec);             //Print final vector, should contain only a single number-string, the final result of the calculations

    }
    catch (runtime_error& rte) {                //Catch thrown exception, print error message
        cout << rte.what() << '\n';
    }

    return 0;
}

/*
Notes:  Need help figuring out string formatting so character variable can be inserted in error messages.

        When implementing () handling, negatives relating to () will hang in equation
        Implement function to call from calculator functions to process negatives - 
        if operator is followed by negative, call process_negative
        process_negative replaces negative and number entries with a negative number entry

        Related to that - how does a function call another function? I think I'm having scope issues.
*/
