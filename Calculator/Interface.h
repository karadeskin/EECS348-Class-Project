#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <map>
#include "Tokenizer.h"
#include "Evaluator.h"

using namespace std;

class Interface {

public:
    string solve_equation(string);

private:
    Tokenizer tokenizer;
    Evaluator evaluator;
    vector<string> tokenize_equation(string);
    string evaluate_equation(vector<string>);
};

#endif
