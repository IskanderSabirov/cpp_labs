#include "employees.h"

int main() {

    std::string cmd, name;
    EmployeesArray vars;

    while (std::cin) {
        std::cin >> cmd;
        if (cmd == "exit") {
            break;
        } else if (cmd == "list") {
            std::cout << vars << std::endl;
        } else if (cmd == "add") {
            int32_t type, salary;
            std::cin >> type;
            if (type != 1 && type != 2)
                std::cerr << "Invalid type of worker, only 1 and 2" << std::endl;
            std::cin >> name >> salary;
            if (type == 1) {
                int32_t bonus;
                std::cin >> bonus;
                vars.add((Employee *) new Developer(name, salary, bonus));
            } else {
                int32_t sold, price;
                std::cin >> sold >> price;
                vars.add((Employee *) new SalesManager(name, salary, sold, price));
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
//            int32_t v;
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
