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
            if (i == 0) {                                       //If so, if it is the first character in the string,
                num_str = character;                            //or if it is the preceding character is not a number,
            }                                                   //then it is the first character of a number-string,
            else if (char_is_num(equ_str[i - 1]) == false) {    //and num_str is set equal to character, the string version of the character
                num_str = character;
            }
            else {                                              //If the character is not the first character of a number-string, but is a number,
                num_str.append(character);                      //append the string version to the end of the num_str string.
            }

            if (i == (equ_str.length() - 1)) {                  //If i is at the end of the vector,
                equ_vec.push_back(num_str);                     //or the next character is not a number,
            }                                                   //the current character is the last character in its number-string.
            else if (char_is_num(equ_str[i + 1]) == false) {    //So, num_str is added to the end of the equ_vec vector
                equ_vec.push_back(num_str);
            }                                                   //If not, nothing is done.
        }
        else if (character == "+") {                            //If the current character is a +,
            if (i == 0 || i == (equ_str.length() - 1)) {        //If '+' is the first or last charcter, throw an error
                throw(runtime_error("Plus operator is missing an operand."));
            }
            else if (char_is_num(equ_str[i - 1]) == true && char_is_num(equ_str[i + 1]) == true) { //'+' is preceded and followed by a number
                equ_vec.push_back(character);                   //add the string version to the end of equ_vec.
            }
            else {                                              //'+' not preceded and followed by a number,
                throw(runtime_error("Plus operator is missing an operand."));   //throw an error

            }
        }
        /*  CODE FOR HANDLING '+' CHARACTER WITH WHITESPACE - UNCOMMENT IF INPUT STRING CAN CONTAIN WHITESPACE - NEEDS TESTING
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
                if (i+2 <= equ_str.length() - 1) {                                   //If '+' is followed by at least two characters
                    if (equ_str[i + 1] == ' ' && char_is_num(equ_str[i + 2]) == true) { //'+' is followed by a space and the character after that is a number
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
        */
        /*  CODE FOR HANDLING SPACES IN INPUT STRING - UNCOMMENT IF INPUT STRING CAN CONTAIN SPACES
        else if (character == " ") {                            //Ignore empty 'whitespace' characters of a single space.
        }
        */
        else {                                                  //If an unrecognized character is detected, print error message and abort loop
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
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
}

int main() {

    string equ_str;                    //Initialize equation variables, and take input of equation
    cout << "Enter equation: ";
    cin >> equ_str;
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
Notes:  Tried to implement whitespace complient code
        cin ends input string when it finds a space
        Can't currently test whitespace code,
        code commented out and left in place
*/
