#include "Interface.h"
#include "Evaluator.h"
#include "Tokenizer.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <map>

using namespace std;

vector<string> Interface::tokenize_equation(string equation) {
    //Tokenize equation string, return result vector
    return tokenizer.tokenize(equation);
}

string Interface::evaluate_equation(vector<string> equ) {
     //Evaluate equation, return first (and only) string in result vector
    return evaluator.eval_equation(equ)[0];
}

string Interface::solve_equation(string equ_string) {
    try {
        vector<string> equ_vec = tokenize_equation(equ_string); //Tokenize input equation
        return evaluate_equation(equ_vec);                      //Evaluate tokenized equation, return result
    }
    catch (runtime_error& rte) {                //Catch thrown  runtime error
        return rte.what();                      //Return specific error message
    }
    catch (out_of_range) {
        return "ERROR: Input out of range.";
    }
    catch (...) {                               //Catch all other errors
        return "ERROR: Unkown error.";          //Return generic error message
    }
}
