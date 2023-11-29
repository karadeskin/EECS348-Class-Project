#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

using namespace std;

class Evaluator {
public:
    vector<string> eval_equation(vector<string> equ_vec);

private:
    void replace_sub_equ(vector<string> &equ_vec, int first_index, int length, string result);

    vector<string> make_sub_vec(vector<string> &equ_vec, int left_index, int right_index);

    void paren_calc(vector<string> &equ_vec);

    void exp_calc(vector<string> &equ_vec);

    void mult_div_mod_calc(vector<string> &equ_vec);

    void add_sub_calc(vector<string> &equ_vec);

};

#endif
