#include "Tokenizer.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

using namespace std;

const char *negative_with_no_operand = "ERROR: Negative sign is missing number.";

// Call function to convert string to vector, assign result to equ_vec
vector<string> Tokenizer::tokenize(string equ_str) {
    equ_str = remove_spaces(equ_str);
    vector<string> equ_vec = str_to_strvec(equ_str);
    return equ_vec;
}

// Return true if character c is a numeral, false if not
bool Tokenizer::char_is_num(char c) {
    return (c >= '0') && (c <= '9');
}

vector<string> Tokenizer::str_to_strvec(string &equ_str) {
    string num_str;                                     //Variable to hold numeric characters, to combine multiple numerals into a single number-string
    vector<string> equ_vec;                             //Variable to hold vector version of equation string
    if (equ_str.size() == 0) {
        equ_vec.push_back("0");
    }
    else {
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
                if ((i > 0 && i < equ_str.length()) && (char_is_num(equ_str[i - 1]) == true || equ_str[i - 1] == ')')
                    && (char_is_num(equ_str[i + 1]) == true || equ_str[i + 1] == '-' || equ_str[i + 1] == '(')) {
                    equ_vec.push_back(character);       //If current character is preceded by number or close paren, and followed by number, minus, or open paren, add character to vector
                }
                else {                                              //character not preceded and followed by allowed characters
                    throw(runtime_error("ERROR: Operator is missing an operand."));   //throw an error
                }
            }
            else if (character == "-") {                            //Current character is a -
                if (i == 0) {                                       //Character is first in string so character is a negative sign
                    if (i == equ_str.length() - 1) {                //Character is at end of string
                        throw(runtime_error("ERROR: Negative sign is missing number."));    //Throw error
                    }
                    else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                        num_str = character;                        //set num_str equal to the character
                    }
                    else if (equ_str[i + 1] == '(') {               //Following character is an open paren
                        equ_vec.push_back(character);               //Add negative sign to equation vector
                    }
                    else {                                          //Negative sign not followed by number
                        throw(runtime_error("ERROR: Negative sign is missing number."));    //Throw error
                    }
                }
                else if (char_is_num(equ_str[i - 1]) == false && equ_str[i - 1] != ')') {    //Proceding character is not a number or close paren so character is a negative sign
                    if (i == equ_str.length() - 1) {                //Character is at end of string
                        throw(runtime_error("ERROR: Negative sign is missing number."));    //Throw error
                    }
                    else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                        num_str = character;                        //set num_str equal to the character
                    }
                    else if (equ_str[i + 1] == '(') {               //Following character is an open paren
                        equ_vec.push_back(character);               //Add negative sign to equation vector
                    }
                    else {                                          //Negative sign not followed by number
                        throw(runtime_error("ERROR: Negative sign is missing number."));    //Throw error
                    }
                }
                else if (i != equ_str.length() - 1) {               //Character is a minus operator, that is not the last character in the string
                    if (char_is_num(equ_str[i + 1]) == true || equ_str[i + 1] == '-' || equ_str[i + 1] == '(') {      //Following character is a number or negative sign or open paren
                        equ_vec.push_back(character);               //add the string version to the end of equ_vec.
                    }
                    else {
                        throw(runtime_error("ERROR: Minus operator is missing an operand."));    //Throw error
                    }
                }
                else {
                    throw(runtime_error("ERROR: Minus operator is missing an operand."));    //Throw error
                }
            }

            else if (character == "(") {                        //If current character is an open paren
                if (i == 0) {                                   //If current character is first character
                    equ_vec.push_back(character);               //Add character to vector
                }
                else if (i == equ_str.length() - 1) {           //If open paren is the last character
                    throw(runtime_error("ERROR: Mismatched parentheses."));    //It is not followed by a close paren, throw error
                }
                else if ((char_is_num(equ_str[i - 1]) == false && equ_str[i - 1] != ')')
                    && (char_is_num(equ_str[i + 1]) == true || equ_str[i + 1] == '-' || equ_str[i + 1] == '(' || equ_str[i + 1] == ')')) {
                    equ_vec.push_back(character);   //If character is preceded by something other than a number or close paren, and is followed by a number, minus, or open or close paren, add to vector
                }
                else {                              //Character is not preceded and followed by allowed characters
                    throw(runtime_error("ERROR: Missing operator or operand."));   //Throw error
                }
            }

            else if (character == ")") {                    //Current character is close paren
                if (i == 0) {                               //Current character is first character
                    throw(runtime_error("ERROR: Mismatched parentheses."));    //Close paren is not preceded by open paren, throw error
                }
                else if (i == equ_str.length() - 1) {       //Character is last character
                    equ_vec.push_back(character);           //Add character to vector
                }
                else if ((char_is_num(equ_str[i - 1]) == true || equ_str[i - 1] == '(' || equ_str[i - 1] == ')') && (char_is_num(equ_str[i + 1]) == false && equ_str[i + 1] != '(')) {
                    equ_vec.push_back(character);           //If character is preceded by number or open or close paren, and not followed by number or open paren, add character to vector
                }
                else {                                      //Character is not preceded and followed by allowed characters
                    throw(runtime_error("ERROR: Missing operator or operand."));   //Throw error
                }
            }

            else {                                                  //If an unrecognized character is detected, print error message and abort loop
                throw(runtime_error("ERROR: Unrecognized character in input."));   //If character not coded for, throw error
            }
        }
    }
    return equ_vec;     //Return created vector
}

string Tokenizer::remove_spaces(string &old_str) {
    string new_str = "";                            //New string to hold result
    string temp_char_str = "a";                     //Temporary variable to hold string conversion of characters
    for (int i = 0; i < old_str.length(); i++) {    //Iterate every index in string
        if (old_str[i] == ' ') {                    //If the current character is a space
            if (i > 0 && i < old_str.length() - 1) {    //If the current character is not the first or last character
                if (char_is_num(old_str[i - 1]) == true && char_is_num(old_str[i + 1]) == true) {   //If the current character is preceded and followed by numbers
                    throw(runtime_error("ERROR: Missing operator."));  //Current character is a space surrounded by numbers. Throw error
                }
                else if (old_str[i + 1] == ' ') {                       //If the next character is also a space
                    throw(runtime_error("ERROR: Extraneous space."));   //Current character is a space followed by a space, throw error
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