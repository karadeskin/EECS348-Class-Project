#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

class Tokenizer {
public:
    std::vector<std::string> tokenize(std::string equ_str);
private:
    bool char_is_num(char c);
    std::vector<std::string> str_to_strvec(std::string &equ_str);
    std::string remove_spaces(std::string &old_str);
};

#endif
