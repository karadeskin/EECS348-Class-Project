#include "Interface.h"
#include "Evaluator.h"
#include "Tokenizer.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <map>

vector<string> Interface::tokenize_equation(string equation) {
    return tokenizer.tokenize(equation);                        //Tokenize equation string, return result vector

    //vector<string> equ_vec = tokenizer.tokenize(equation);
    //return equ_vec;
}

string Interface::evaluate_equation(vector<string> equ) {
    return evaluator.eval_equation(equ)[0];                 //Evaluate equation, return first (and only) string in result vector
    
    //string result = evaluator.eval_equation(equ)[0];
    //return result;
}

string Interface::solve_equation(string equ_string) {
    try {
        vector<string> equ_vec = tokenize_equation(equ_string); //Tokenize input equation
        return evaluate_equation(equ_vec);                      //Evaluate tokenized equation, return result
    }
    catch (runtime_error& rte) {                //Catch thrown exception
        return rte.what();                      //Return error message
    }
}
