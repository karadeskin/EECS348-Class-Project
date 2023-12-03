#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

class Evaluator {
public:
    std::vector<std::string> eval_equation(std::vector<std::string> equ_vec);

private:
    void replace_sub_equ(std::vector<std::string> &equ_vec, int first_index, int length, std::string result);

    std::vector<std::string> make_sub_vec(std::vector<std::string> &equ_vec, int left_index, int right_index);

    void paren_calc(std::vector<std::string> &equ_vec);

    void exp_calc(std::vector<std::string> &equ_vec);

    void mult_div_mod_calc(std::vector<std::string> &equ_vec);

    void add_sub_calc(std::vector<std::string> &equ_vec);

};

#endif
