#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

using namespace std;

class Tokenizer {
public:
    vector<string> tokenize(string equ_str);

private:
    bool char_is_num(const char c);

    vector<string> str_to_strvec(string &equ_str);

    string remove_spaces(string &old_str);

};

#endif
