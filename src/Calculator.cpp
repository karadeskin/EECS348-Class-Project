#include <iostream>
#include <vector>
#include <iterator>
#include <string>

template <typename T>
void vec_print(const std::vector<T>& container) {   //Print vector, entry by entry
    for (const T& object : container)              //Found online, modified to generic type
        std::cout << object << ' ';
    std::cout << std::endl;
}

bool char_is_num(const char c) {        //Return true if character c is a numeral, false if not
    if ((c >= '0') and (c <= '9')) {
        return true;
    }
    else {
        return false;
    }
}

std::vector<std::string> str_to_strvec(std::string equ_str) {
    std::string num_str;                                    //Variable to hold numeric characters, to combine multiple numerals into a single number-string
    std::vector<std::string> equ_vec;                       //Variable to hold vector version of equation string
    for (int i = 0; i < equ_str.length(); i++) {              //Iterate i over indices in equ_str vector
        std::string character = { equ_str[i] };               //Define character variable as a string, and assign the string conversion of the entry of equ_str at index i

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
            equ_vec.push_back(character);                       //add the string version to the end of equ_vec.
        }
        else {                                                  //If an unrecognized character is detected, print error message and abort loop
            std::cout << "ERROR: Unrecognized input: " << character << std::endl;   // - needs implementation of actual error handling process
            break;
        }
    }
    return equ_vec;     //Return created vector
}

std::vector<std::string> add_sub_calc(std::vector<std::string> equ_vec) {
    bool found_operator = false;            //Variable to track if we completed a pass through the equation without finding an operator
    do {
        found_operator = false;             //Reset found operator tracker to false
        int result;                         //Variable to store the result
        for (int i = 0; i < equ_vec.size(); i++) {   //Iterate over indices in equ_vec
            if (equ_vec[i] == "+") {               //If the entry at current index is a +,
                found_operator = true;      //Update operator tracker
                result = std::stoi(equ_vec[(i - 1)]) + std::stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the left operand from the equation vector
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the operator from the equation vector
                equ_vec.erase(equ_vec.begin() + (i - 1));           //Remove the right operand from the equation vector
                equ_vec.insert(equ_vec.begin() + (i - 1), std::to_string(result));  //Convert the result to a string, and insert it where the left operand was
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues. 
                                        //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
    return equ_vec;     //Return vector with results of calculation
}

int main() {

    std::string equ_str;                    //Initialize equation variables, and take input of equation
    std::cout << "Enter equation: ";
    std::cin >> equ_str;
    std::vector<std::string> equ_vec;

    equ_vec = str_to_strvec(equ_str);       //Call function to convert string to vector, assign result to equ_vec

    vec_print<std::string>(equ_vec);        //Print equation vector for verification purposes - remove before final submission
    std::cout << "\n\n";

    equ_vec = add_sub_calc(equ_vec);        //Call function to perform addition/subtracting calculations (subtraction still to be added)

    vec_print<std::string>(equ_vec);    //Print final vector, should contain only a single number-string, the final result of the calculations

    return 0;
}

/*
Notes:  str_to_strvec input can probably be converted to a reference.
        I'm not sure how to do that, and need some assistance.

        add_sub_calc is probably in the same situation,
        but that may conflict with the parentheses handling process.
        I'm not exactly sure how that is going to work yet.
        Still, it can probably be converted to a reference now,
        and converted back later if necessary.
*/