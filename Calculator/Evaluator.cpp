#include "Evaluator.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

using namespace std;

vector<string> Evaluator::eval_equation(vector<string> equ_vec) {
    paren_calc(equ_vec);                        // Pass inputted equation vector to begin evaluation process
    return equ_vec;                            // Return the equation vector
}

void Evaluator::replace_sub_equ(vector<string> &equ_vec, int first_index, int length, string result) {
    // could use: equ_vec.erase(equ_vec.begin() + first_index, equ_vec.begin() + first_index + (length - 1));
    for (int i = first_index; i <= first_index + (length-1); i++) {     //Remove sub-equation from equation vector
        equ_vec.erase(equ_vec.begin() + first_index);
    }
    equ_vec.insert(equ_vec.begin() + first_index, result);  //Insert result where the left operand was
}

vector<string> Evaluator::make_sub_vec(vector<string> &equ_vec, int left_index, int right_index) {
    vector<string> sub_vec;                                     //Initialize variable for sub vector
    for (int i = left_index; i <= right_index; i++) {           //Iterate over indices from start position to end position
        sub_vec.push_back(equ_vec[i]);                          //For each index, add that value to sub_vec
    }
    return sub_vec;                                             //Return sub_vec
}

void Evaluator::paren_calc(vector<string> &equ_vec) {
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
                        break;          //End for loop to restart checking from left side
                    }
                }
                else {                  //If close paren is not matched to an open paren, throw error
                    throw(runtime_error("ERROR: Mismatched parentheses."));
                }
            }
        }
        if (found_left_paren != found_right_paren) {            //Check if we have not found both an open and close paren
            throw(runtime_error("ERROR: Mismatched Parentheses."));    //If so, throw error
        }
    } while (found_left_paren == true && found_right_paren == true);    //Loop while we have found both an open and close paren
    exp_calc(equ_vec);      //Once parentheses have been resolved, pass remaining equation to rest of calculation functions
}

void Evaluator::exp_calc(vector<string> &equ_vec) {
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

void Evaluator::mult_div_mod_calc(vector<string> &equ_vec) {
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
                    throw(runtime_error("ERROR: Cannot divide by zero.")); //You cannot divide by zero, throw error
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
                if (stoi(equ_vec[i + 1]) == 0) {        //If / is followed by a zero
                    throw(runtime_error("ERROR: Cannot divide by zero.")); //You cannot divide by zero, throw error
                }

                found_operator = true;      //Update operator tracker
                if (equ_vec[i + 1] == "-") {            //If % character followed by - character, - is negative sign for following number
                    replace_sub_equ(equ_vec, i + 1, 2, to_string(-1 * stoi(equ_vec[i + 2])));   //Replace negative and following number with the number times negative one
                }

                if (stoi(equ_vec[i - 1]) < 0) {                                         //If % character preceded by a negative number
                    int remainder = (-1 * stoi(equ_vec[(i - 1)])) % stoi(equ_vec[(i + 1)]);  //Negate negative number, calculate remainder
                    result = stoi(equ_vec[(i + 1)]) - remainder;                            //Calculate modulo by subtracting remainder from divisor
                    //replace_sub_equ(equ_vec, i - 1, 1, to_string(-1 * stoi(equ_vec[i - 1])));   //Replace negative and following number with the number times negative one
                }
                else {                                                              //If preceding number is positive, calculate modulo
                    result = stoi(equ_vec[(i - 1)]) % stoi(equ_vec[(i + 1)]);     //Convert the entries on either side of the operator to strings, and perform the operation
                }
                replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues.
    //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
    add_sub_calc(equ_vec);              //Call addition and subtraction function
}

void Evaluator::add_sub_calc(vector<string> &equ_vec) {
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
                if (i != 0 && equ_vec.size() != 1) {                                          //If vector is only one entry long, or the negative sign is the first character, we already have our result and don't need to do anything else.
                    result = stoi(equ_vec[(i - 1)]) - stoi(equ_vec[(i + 1)]);       //If vector isn't one entry long, convert the entries on either side of the operator to strings, and perform the operation
                    replace_sub_equ(equ_vec, i - 1, 3, to_string(result));         //Replace sub-equation with result
                }
                break;      //End the for loop, so we can restart the iteration from the left side
            }
        }
    } while (found_operator == true);   //If we found an operator, found_operator was updated to true, loop continues.
    //Otherwise, there are no more operators in the equation, found_operator remains false, loop ends
}