#ifndef __CALC_INTERFACE_H__
#define __CALC_INTERFACE_H__

#include <string>
#include <vector>

#include "Tokenizer.h"
#include "Evaluator.h"

class Interface {
public:
    std::string solve_equation(std::string);
private:
    Tokenizer tokenizer;
    Evaluator evaluator;

    std::vector<std::string> tokenize_equation(std::string);
    std::string evaluate_equation(std::vector<std::string>);
};

#endif // __CALC_INTERFACE_H__
