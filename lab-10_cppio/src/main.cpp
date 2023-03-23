#include <iostream>
#include <string>
#include <algorithm>
#include "employees.h"

bool isNumeric(std::string const &str) {
    auto it = std::find_if(str.begin(), str.end(), [](char const &c) {
        return !std::isdigit(c);
    });

    return !str.empty() && it == str.end();
}

int main() {

    std::string cmd, name, arg2;
    EmployeesArray vars;

    while (std::cin) {
        std::cin >> cmd;
        if (cmd == "exit") {
            break;
        } else if (cmd == "list") {
            std::cout << vars;
        } else if (cmd == "add") {
            std::size_t type, salary, bonus;
            std::cin >> type;
            std::cin >> name >> salary >> bonus;
            if (type == 1) {
                vars.add(new Developer(name.c_str(), salary, bonus));
            }else{
                std::cerr<<"Invalid type of worker, only 1 and 2" << std::endl;
            }
        } else {
            return -1;
        }
//        } else if (cmd == "get") {
//            std::size_t i, j;
//            std::cin >> arg1 >> i >> j;
//            assert(vars.count(arg1) && "Unknows var");
//            std::cout << vars[arg1]->get(i, j) << std::endl;
//        } else if (cmd == "set") {
//            std::size_t i, j;
//            int v;
//            std::cin >> arg1 >> i >> j >> v;
//            assert(vars.count(arg1) && "Unknows var");
//            vars[arg1]->set(i, j, v);
//        } else if (cmd == "print") {
//            std::cin >> arg1;
//            assert(vars.count(arg1) && "Unknows var");
//            vars[arg1]->print(stdout);
//        } else if (cmd == "cp_init") {
//            std::cin >> arg1 >> arg2;
//            assert(!vars.count(arg1) && "Already created var");
//            assert(vars.count(arg2) && "Unknows var");
//            vars[arg1] = new Matrix(*vars[arg2]);
//        } else if (cmd == "=") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg2) && "Unknows var");
//            if (vars.count(arg1) == 0) {
//                vars[arg1] = new Matrix(0, 0);
//            }
//            *vars[arg1] = *vars[arg2];
//        } else if (cmd == "==") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            std::cout << (*vars[arg1] == *vars[arg2]) << std::endl;
//        } else if (cmd == "!=") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            std::cout << (*vars[arg1] != *vars[arg2]) << std::endl;
//        } else if (cmd == "+=") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            *vars[arg1] += *vars[arg2];
//        } else if (cmd == "-=") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            *vars[arg1] -= *vars[arg2];
//        } else if (cmd == "*=") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            *vars[arg1] *= *vars[arg2];
//        } else if (cmd == "+") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            (*vars[arg1] + *vars[arg2]).print(stdout);
//        } else if (cmd == "-") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            (*vars[arg1] - *vars[arg2]).print(stdout);
//        } else if (cmd == "*") {
//            std::cin >> arg1 >> arg2;
//            assert(vars.count(arg1) && "Unknows var");
//            assert(vars.count(arg2) && "Unknows var");
//            (*vars[arg1] * *vars[arg2]).print(stdout);
//        }
    }
    return 0;
}
