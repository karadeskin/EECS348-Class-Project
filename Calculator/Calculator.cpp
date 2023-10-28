#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

template <typename T>
void vec_print(const vector<T>& container) {   //Print vector, entry by entry
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
                equ_vec.push_back(num_str);                     //add num_str to equ_vec
                num_str = "";                                   //Reset num_str
            }
            else if (char_is_num(equ_str[i + 1]) == false) {    //If it is not followed by a number
                if (equ_str[i + 1] == ' ') {                    //Characer is followed by a space
                    if (i + 1 == equ_str.length() - 1) {        //Space is the last character
                        equ_vec.push_back(num_str);                     //add num_str to equ_vec
                        num_str = "";                            //Reset num_str
                    }
                    else if (char_is_num(equ_str[i + 2]) == false) {    //Character is followed by a space, then not a number
                        equ_vec.push_back(num_str);                     //add num_str to equ_vec
                        num_str = "";                           //Reset num_str
                    }
                }
                else {                                          //Character is not followed by number or space
                    equ_vec.push_back(num_str);                     //add num_str to equ_vec
                    num_str = "";                           //Reset num_str
                }
            }
        }

        else if (character == "+") {                            //If the current character is a +,
            if (i == 0 || i == (equ_str.length() - 1)) {        //If '+' is the first or last charcter, throw an error
                throw(runtime_error("Plus operator is missing an operand."));
            }
            else if (char_is_num(equ_str[i - 1]) == true && char_is_num(equ_str[i + 1]) == true) { //'+' is preceded and followed by a number
                equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
            }
            else if (char_is_num(equ_str[i - 1]) == false && char_is_num(equ_str[i + 1]) == true) { //'+' is followed by a number, but not preceded
                if (i >= 2) {                                   //If '+' is preceded by at least two characters
                    if (equ_str[i - 1] == ' ' && char_is_num(equ_str[i - 2]) == true) { //'+' is preceded by a space and the character before that is a number
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else {                                      //'+' is not preceded by number, space
                        throw(runtime_error("Plus operator is missing an operand."));   //Throw error
                    }
                }
                else {                                          //'+' is not preceded by at least two characters
                    throw(runtime_error("Plus operator is missing an operand."));   //Throw error
                }
            }
            else if (char_is_num(equ_str[i - 1]) == true && char_is_num(equ_str[i + 1]) == false) { //'+' is preceded by a number, but not followed
                if (i + 2 <= equ_str.length() - 1) {                                   //If '+' is followed by at least two characters
                    if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2]) == true) { //'+' is followed by a space and the character after that is a number
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else if (equ_str[i + 1] == ' ' && equ_str[i + 2] == '-') {      //'+' is followed by a space and a negative
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else if (equ_str[i + 1] == '-') {                   //'+' is followed by a negative
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else {                                      //'+' is not followed by number, space
                        throw(runtime_error("Plus operator is missing an operand."));   //Throw error
                    }
                }
                else {                                          //'+' is not followed by at least two characters
                    throw(runtime_error("Plus operator is missing an operand."));   //Throw error
                }
            }
            else if (char_is_num(equ_str[i - 1]) == false && char_is_num(equ_str[i + 1]) == false) { //'+' is not preceded or followed by a number
                if (i >= 2 && i + 2 <= equ_str.length() - 1) {                                   //If '+' is proceded and followed by at least two characters
                    if ((equ_str[i - 1] == ' ' && char_is_num(equ_str[i - 2]) == true) && (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2]) == true)) { //'+' is preceded and followed by a space and the characters before/after those are numbers
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else if ((equ_str[i - 1] == ' ' && char_is_num(equ_str[i - 2]) == true) && (equ_str[i + 1] == ' ' && equ_str[i + 2] == '-')) { //'+' is preceded preceded by a number and a space, and followed by a space and a negative
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else if ((equ_str[i - 1] == ' ' && char_is_num(equ_str[i - 2]) == true) && equ_str[i + 1] == '-') { //'+' is preceded preceded by a number and a space, and followed by a negative
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else {                                      //'+' is not followed by number, space
                        throw(runtime_error("Plus operator is missing an operand."));   //Throw error
                    }
                }
                else {                                          //'+' is not followed by at least two characters
                    throw(runtime_error("Plus operator is missing an operand."));   //Throw error
                }
            }
            else {                                              
                throw(runtime_error("Plus operator is missing an operand."));   //Throw error
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
                else if (i + 2 <= equ_str.length() - 1) {       //Character is followed by at least two characters
                    if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2])) {  //Character is followed by a space then a number
                        num_str = character;                        //set num_str equal to the character
                    }
                    else {                                      //Negative sign is not followed by a space then a number
                        throw(runtime_error("Negative sign is missing number."));    //Throw error
                    }
                }
                else {                                          //Negative sign not followed by number
                    throw(runtime_error("Negative sign is missing number."));    //Throw error
                }
            }
            else if (i == 1) {                                  //Character is second in string
                if (equ_str[i - 1] == ' ') {                    //Preceding character is a space
                    if (i == equ_str.length() - 1) {                //Character is at end of string
                        throw(runtime_error("Negative sign is missing number."));    //Throw error
                    }
                    else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                        num_str = character;                        //set num_str equal to the character
                    }
                    else if (i + 2 <= equ_str.length() - 1) {       //Character is followed by at least two characters
                        if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2])) {  //Character is followed by a space then a number
                            num_str = character;                        //set num_str equal to the character
                        }
                        else {                                      //Negative sign is not followed by a space then a number
                            throw(runtime_error("Negative sign is missing number."));    //Throw error
                        }
                    }
                    else {                                          //Negative sign not followed by number
                        throw(runtime_error("Negative sign is missing number."));    //Throw error
                    }
                }
                else if (char_is_num(equ_str[i - 1]) == true) {     //Preceding character is a number, character is a minus sign
                    if (i == equ_str.length() - 1) {                //Character is last character
                        throw(runtime_error("Minus operator is missing an operand."));   //Throw error
                    }
                    else if (i + 1 == equ_str.length() - 1) {       //Character is followed by one character
                        if (char_is_num(equ_str[i + 1]) == true) {  //Character is followed by a number
                            equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                        }
                        else {                                      //Character is not followed by a number
                            throw(runtime_error("Minus operator is missing an operand.")); //Throw error
                        }
                    }
                    else if (i + 2 <= equ_str.length() - 1) {       //Character is followed by at least two characters
                        if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2])) {  //Character is followed by a space then a number
                            equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                        }
                        else {                                      //Minus sign is not followed by a space then a number
                            throw(runtime_error("Minus operator is missing an operand."));    //Throw error
                        }
                    }
                    else {                                          //Character is not preceded by a space or a number
                        throw(runtime_error("Minus operator is missing an operand,"));   //Throw error
                    }
                }
                else {                                              //Preceding character is not a space or number
                    throw(runtime_error("Missing operand."));        //Throw error
                }
            }
            else if (char_is_num(equ_str[i - 1]) == false) {    //Preceding character is not a number
                if (equ_str[i - 1] == ' ')  {   //Character is preceded by a space
                    if (char_is_num(equ_str[i - 2]) == true) {      //The preceding space is preceded by a number
                        if (i == equ_str.length() - 1) {                //Character is last character
                            throw(runtime_error("Minus operator is missing an operand."));   //Throw error
                        }
                        else if (i + 1 == equ_str.length() - 1) {       //Character is followed by one character
                            if (char_is_num(equ_str[i + 1]) == true) {  //Character is followed by a number
                                equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                            }
                            else {                                      //Character is not followed by a number
                                throw(runtime_error("Minus operator is missing an operand.")); //Throw error
                            }
                        }
                        else if (i + 2 <= equ_str.length() - 1) {       //Character is followed by at least two characters
                            if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2])) {  //Character is followed by a space then a number
                                equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                            }
                            else {                                      //Minus sign is not followed by a space then a number
                                throw(runtime_error("Minus operator is missing an operand."));    //Throw error
                            }
                        }
                        else {                                          //Character is not preceded by a space or a number
                            throw(runtime_error("Minus operator is missing an operand,"));   //Throw error
                        }
                    }
                    else {                                              //The preceding space is not preceded by a number, character is a negative sign
                        if (i == equ_str.length() - 1) {                //Character is at end of string
                            throw(runtime_error("Negative sign is missing number."));    //Throw error
                        }
                        else if (i + 1 == equ_str.length() - 1) {       //Character is followed by one character
                            if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                                num_str = character;                        //set num_str equal to the character
                            }
                            else {                                      //Following character is not a number
                                throw(runtime_error("Minus operator is missing an operand,"));   //Throw error
                            }
                        }
                        else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                            num_str = character;                        //set num_str equal to the character
                        }
                        else if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2])) {    //Character is followed by a space and a number
                            num_str = character;                        //set num_str equal to the character
                        }
                        else {                                          //Negative sign not followed by number
                            throw(runtime_error("Negative sign is missing number."));    //Throw error
                        }
                    }
                }
                else {                                          //Preceding character is not a number or space, character is a negative sign
                    if (i == equ_str.length() - 1) {                //Character is at end of string
                        throw(runtime_error("Negative sign is missing number."));    //Throw error
                    }
                    else if (i + 1 == equ_str.length() - 1) {       //Character is followed by one character
                        if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                            num_str = character;                        //set num_str equal to the character
                        }
                        else {                                      //Following character is not a number
                            throw(runtime_error("Minus operator is missing an operand,"));   //Throw error
                        }
                    }
                    else if (char_is_num(equ_str[i + 1]) == true) { //Following character is a number
                        num_str = character;                        //set num_str equal to the character
                    }
                    else if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2])) {    //Character is followed by a space and a number
                        num_str = character;                        //set num_str equal to the character
                    }
                    else {                                          //Negative sign not followed by number
                        throw(runtime_error("Negative sign is missing number."));    //Throw error
                    }
                }
            }
            else {                                                  //Character is not first or second character, and is preceded by a number
                if (i == equ_str.length() - 1) {                //Character is last character
                    throw(runtime_error("Minus operator is missing an operand."));   //Throw error
                }
                else if (i + 1 == equ_str.length() - 1) {       //Character is followed by one character
                    if (char_is_num(equ_str[i + 1]) == true) {  //Character is followed by a number
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else {                                      //Character is not followed by a number
                        throw(runtime_error("Minus operator is missing an operand.")); //Throw error
                    }
                }
                else {                                          //Character is followed by at least two characters
                    if (char_is_num(equ_str[i + 1]) == true) {  //Character is followed by a number
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else if (equ_str[i + 1] = ' ' && char_is_num(equ_str[i + 2]) == true) { //Character is followed by a space and a number
                        equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
                    }
                    else {                                      //Character is not followed by number or space and number
                        throw(runtime_error("Minus operator is missing an operand.")); //Throw error
                    }
                }
            }
        }

        else if (character == " ") {                            //Ignore empty 'whitespace' characters of a single space.
            if (i == 0 || i == (equ_str.length() - 1)) {        //If space is the first or last charcter, do nothing

            }
            else if (char_is_num(equ_str[i - 1]) == true && char_is_num(equ_str[i + 1]) == true) {  //If space is preceded and followed by numbers
                throw(runtime_error("Missing operand."));                //Throw error
            }
        }
        

        else {                                                  //If an unrecognized character is detected, print error message and abort loop
            cout << character << '\n';
            throw(runtime_error("Unrecognized character in input."));   //If character not coded for, throw error
        }
    }
    return equ_vec;     //Return created vector
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
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the left operand from the equation vector
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the operator from the equation vector
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the right operand from the equation vector
                equ_vec.insert(equ_vec.begin() + (i - 1), to_string(result));  //Convert the result to a string, and insert it where the left operand was
                break;      //End the for loop, so we can restart the iteration from the left side
            }
            else if (equ_vec[i] == "-") {               //If the entry at current index is a -,
                found_operator = true;      //Update operator tracker
                result = stoi(equ_vec[(i - 1)]) - stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the left operand from the equation vector
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the operator from the equation vector
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the right operand from the equation vector
                equ_vec.insert(equ_vec.begin() + (i - 1), to_string(result));  //Convert the result to a string, and insert it where the left operand was
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
}

int main() {

    string equ_str;                    //Initialize equation variables, and take input of equation
    cout << "Enter equation: ";
    getline(cin, equ_str);
    vector<string> equ_vec;

    try {
        equ_vec = str_to_strvec(equ_str);       //Call function to convert string to vector, assign result to equ_vec
        vec_print<string>(equ_vec);             //Print equation vector for verification purposes - remove before final submission
        cout << "\n\n";

        add_sub_calc(equ_vec);        //Call function to perform addition/subtracting calculations (subtraction still to be added)

        vec_print<string>(equ_vec);             //Print final vector, should contain only a single number-string, the final result of the calculations

    }
    catch (runtime_error& rte) {                //Catch thrown exception, print error message
        cout << rte.what() << '\n';
    }

    
    return 0;
}

/*
Notes:  I think whitespace code is implemented, but it needs more testing.
        Input in the form of -a- b, where a and b are numbers,
        causes issues because the space turns into a smiley-face character.
        As best as I can tell, this happens when the input string is passed to the calculator function.
        If I disable the throw command for unrecognized characters, everything works fine for that input.
*/
