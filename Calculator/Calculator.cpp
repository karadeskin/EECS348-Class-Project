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
    string num_str;                                     //Variable to hold numeric characters, to combine multiple numerals into a single number-string
    vector<string> equ_vec;                             //Variable to hold vector version of equation string
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
            else if ((char_is_num(equ_str[i - 1]) == true || equ_str[i - 1] == ')') && (char_is_num(equ_str[i + 1]) == true || equ_str[i + 1] == '-' || equ_str[i + 1] == '(')) {
                equ_vec.push_back(character);       //If current character is preceded by number or close paren, and followed by number, minus, or open paren, add character to vector
            }
            else {                                              //character not preceded and followed by allowed characters
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
                else if (equ_str[i + 1] == '(') {               //Following character is an open paren
                    equ_vec.push_back(character);               //Add negative sign to equation vector
                }
                else {                                          //Negative sign not followed by number
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
            }
            else if (char_is_num(equ_str[i - 1]) == false && equ_str[i-1] != ')') {    //Proceding character is not a number or close paren so character is a negative sign
                if (i == equ_str.length() - 1) {                //Character is at end of string
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
                else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                    num_str = character;                        //set num_str equal to the character
                }
                else if (equ_str[i + 1] == '(') {               //Following character is an open paren
                    equ_vec.push_back(character);               //Add negative sign to equation vector
                }
                else {                                          //Negative sign not followed by number
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
            }
            else if (i != equ_str.length() - 1) {               //Character is a minus operator, that is not the last character in the string
                if (char_is_num(equ_str[i + 1]) == true || equ_str[i + 1] == '-' || equ_str[i+1] == '(') {      //Following character is a number or negative sign or open paren
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

        else if (character == "(") {                        //If current character is an open paren
            if (i == 0) {                                   //If current character is first character
                equ_vec.push_back(character);               //Add character to vector
            }
            else if (i == equ_str.length() - 1) {           //If open paren is the last character
                throw(runtime_error("Mismatched parentheses."));    //It is not followed by a close paren, throw error
            }
            else if ((char_is_num(equ_str[i - 1]) == false && equ_str[i-1] != ')') && (char_is_num(equ_str[i + 1]) == true || equ_str[i + 1] == '-' || equ_str[i+1] == '(' || equ_str[i+1] == ')')) {
                equ_vec.push_back(character);   //If character is preceded by something other than a number or close paren, and is followed by a number, minus, or open or close paren, add to vector
            }
            else {                              //Character is not preceded and followed by allowed characters
                throw(runtime_error("Missing operator or operand."));   //Throw error
            }
        }

        else if (character == ")") {                    //Current character is close paren
            if (i == 0) {                               //Current character is first character
                throw(runtime_error("Mismatched parentheses."));    //Close paren is not preceded by open paren, throw error
            }
            else if (i == equ_str.length() - 1) {       //Character is last character
                equ_vec.push_back(character);           //Add character to vector
            }
            else if ((char_is_num(equ_str[i - 1]) == true || equ_str[i-1] == '(' || equ_str[i-1] == ')') && (char_is_num(equ_str[i + 1]) == false && equ_str[i + 1] != '(')) {
                equ_vec.push_back(character);           //If character is preceded by number or open or close paren, and not followed by number or open paren, add character to vector
            }
            else {                                      //Character is not preceded and followed by allowed characters
                throw(runtime_error("Missing operator or operand."));   //Throw error
            }
        }

        else {                                                  //If an unrecognized character is detected, print error message and abort loop
            throw(runtime_error("Unrecognized character in input."));   //If character not coded for, throw error
        }
    }
    return equ_vec;     //Return created vector
}

void replace_sub_equ(vector<string> &equ_vec, int first_index, int length, string result) {
    for (int i = first_index; i <= first_index + (length-1); i++) {     //Remove sub-equation from equation vector
        equ_vec.erase(equ_vec.begin() + first_index);
    }
    equ_vec.insert(equ_vec.begin() + first_index, result);  //Insert result where the left operand was
}



void add_sub_calc(vector<string> &equ_vec) {
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int result;                         //Variable to store the result
        for (int i = 0; i < equ_vec.size(); i++) {   //Iterate over indices in equ_vec
            if (equ_vec[i] == "+") {               //If the entry at current index is a +,
                found_operator = true;      //Update operator tracker
                if (equ_vec[i + 1] == "-") {            //If + character is followed by - character, - is a negative sign for the number after that
                    replace_sub_equ(equ_vec, i + 1, 2, to_string(-1 * stoi(equ_vec[i + 2])));   //Replace negative sign and number with the number times negative one
                }
                result = stoi(equ_vec[(i - 1)]) + stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            else if (equ_vec[i] == "-") {               //If the entry at current index is a -,
                found_operator = true;      //Update operator tracker
                if (equ_vec[i + 1] == "-") {    //If - character is followed by - character, second - is a negative sign for the number after that
                    replace_sub_equ(equ_vec, i + 1, 2, to_string(-1 * stoi(equ_vec[i + 2])));   //Replace negative sign and number with the number times negative one
                }
                else if (i == 0) {              //If - character is the first character, - is a negative sign for the following number
                    replace_sub_equ(equ_vec, i, 2, to_string(-1 * stoi(equ_vec[i + 1])));   //Replace negative sign and number with the number times negative one
                }
                if (equ_vec.size() != 1) {                                          //If vector is only one entry long, we already have our result and don't need to do anything else.
                    result = stoi(equ_vec[(i - 1)]) - stoi(equ_vec[(i + 1)]);       //If vector isn't one entry long, convert the entries on either side of the operator to strings, and perform the operation
                    replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
                }
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
}

void mult_div_mod_calc(vector<string> &equ_vec) {
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int result;                         //Variable to store the result
        for (int i = 0; i < equ_vec.size(); i++) {   //Iterate over indices in equ_vec
            if (equ_vec[i] == "*") {               //If the entry at current index is a *,
                found_operator = true;      //Update operator tracker
                if (equ_vec[i + 1] == "-") {        //If * character is followed by - character, - is negative sign for following number
                    replace_sub_equ(equ_vec, i + 1, 2, to_string(-1 * stoi(equ_vec[i + 2])));   //Replace negative and following number with the number times negative one
                }
                result = stoi(equ_vec[(i - 1)]) * stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            else if (equ_vec[i] == "/") {               //If the entry at current index is a /,
                if (stoi(equ_vec[i + 1]) == 0) {        //If / is followed by a zero
                    throw(runtime_error("Cannot divide by zero.")); //You cannot divide by zero, throw error
                }
                found_operator = true;      //Update operator tracker
                if (equ_vec[i + 1] == "-") {        //If / character followed by - character, - is negative sign for following number
                    replace_sub_equ(equ_vec, i + 1, 2, to_string(-1 * stoi(equ_vec[i + 2])));   //Replace negative and following number with the number times negative one
                }
                result = stoi(equ_vec[(i - 1)]) / stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            else if (equ_vec[i] == "%") {               //If the entry at current index is a %,
                found_operator = true;      //Update operator tracker
                if (equ_vec[i + 1] == "-") {            //If % character followed by - character, - is negative sign for following number
                    replace_sub_equ(equ_vec, i + 1, 2, to_string(-1 * stoi(equ_vec[i + 2])));   //Replace negative and following number with the number times negative one
                }
                result = stoi(equ_vec[(i - 1)]) % stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
    add_sub_calc(equ_vec);              //Call addition and subtraction function
}

void exp_calc(vector<string> &equ_vec) {
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int result;                         //Variable to store the result
        for (int i = 0; i < equ_vec.size(); i++) {   //Iterate over indices in equ_vec
            if (equ_vec[i] == "^") {               //If the entry at current index is a ^,
                found_operator = true;      //Update operator tracker
                if (equ_vec[i + 1] == "-") {        //If ^ character followed by - character, - is negative sign for following number
                    replace_sub_equ(equ_vec, i + 1, 2, to_string(-1 * stoi(equ_vec[i + 2])));   //Replace negative and following number with the number times negative one
                }
                result = pow(stoi(equ_vec[(i - 1)]), stoi(equ_vec[(i + 1)]));   //Convert operands to integers, pass to power function, assign results to result
                replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
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

vector<string> make_sub_vec(vector<string> &equ_vec, int left_index, int right_index) {     //Return a vector that is a subset of original vector
    vector<string> sub_vec;                                     //Initialize variable for sub vector
    for (int i = left_index; i <= right_index; i++) {           //Iterate over indices from start position to end position
        sub_vec.push_back(equ_vec[i]);                          //For each index, add that value to sub_vec
    }
    return sub_vec;                                             //Return sub_vec
}

void paren_calc(vector<string> &equ_vec) {                      //Resolve parentheses in equation
    bool found_left_paren = false;                      //Initialize variables to track if parentheses have been found
    bool found_right_paren = false;
    do {
        found_left_paren = found_right_paren = false;       //Reset tracker variables to false
        vector<string> sub_vec;                             //Initialize variable to hold sub vector
        int left_paren_index = 0;                           //Initialize variable to track index of last found open paren
        for (int i = 0; i < equ_vec.size(); i++) {          //Iterate over each entry in the variable
            if (equ_vec[i] == "(") {                //If the entry is an open paren, update index and tracker variables
                left_paren_index = i;
                found_left_paren = true;
            }
            else if (equ_vec[i] == ")") {           //If the entry is a close paren
                if (found_left_paren == true) {     //Check if we have found a corresponding open paren
                    found_right_paren = true;       //If so, update right_paren tracker
                    if (left_paren_index + 1 == i) {        //If parentheses are empty - have nothing between them
                        replace_sub_equ(equ_vec, left_paren_index, 2, "0"); //replace them with a zero
                    }
                    else {                              //If parentheses are not empty
                        sub_vec = make_sub_vec(equ_vec, left_paren_index + 1, i - 1);   //Make sub-vector from the contents of parentheses
                        exp_calc(sub_vec);          //Resolve the sub-vector
                        replace_sub_equ(equ_vec, left_paren_index, i - left_paren_index + 1, sub_vec[0]);   //Replace the parentheses and their contents with the result of their contents
                        vec_print(equ_vec);
                        break;          //End for loop to restart checking from left side
                    }
                }
                else {                  //If close paren is not matched to an open paren, throw error
                    throw(runtime_error("Mismatched parentheses."));
                }
            }
        }
        if (found_left_paren != found_right_paren) {            //Check if we have not found both an open and close paren
            throw(runtime_error("Mismatched Parentheses."));    //If so, throw error
        }
    } while (found_left_paren == true && found_right_paren == true);    //Loop while we have found both an open and close paren
    exp_calc(equ_vec);      //Once parentheses have been resolved, pass remaining equation to rest of calculation functions
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

        paren_calc(equ_vec);                    //Start calculation function sequence

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
*/
