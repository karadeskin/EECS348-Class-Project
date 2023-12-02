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

int main(int argc, char *argv[]) {
	Interface interface;

    if (argc == 2) {
        string equ_str = argv[1];
        auto result = interface.solve_equation(equ_str);
        std::cout << result << '\n';
        return std::stoi(result);
    }

    while (1) {
        string equ_str;                    //Initialize equation variables, and take input of equation
        cout << "Enter equation: ";
        getline(cin, equ_str);
        if (equ_str == "xxxx") {
            break;
        }

        cout << interface.solve_equation(equ_str) << '\n';
    }
    return 0;
}