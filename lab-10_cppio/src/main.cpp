#include <fstream>
#include "employees.h"

namespace {

    void list(employee::EmployeesArray &vars) {
        std::cout << vars << std::endl;
    }

    void add(employee::EmployeesArray &vars) {
        int32_t type;
        std::cin >> type;
        if (type != 1 && type != 2)
            std::cerr << "Invalid type of worker, only 1 and 2" << std::endl;
        if (type == 1) {
            auto e = new employee::Developer();
            std::cin >> *e;
            vars.add(e);
        } else {
            auto e = new employee::SalesManager();
            std::cin >> *e;
            vars.add(e);
        }
    }

    void save(employee::EmployeesArray &vars) {
        std::string file;
        std::cin >> file;
        std::ofstream out(file, std::ios::out);
        if (out) {
            out << vars;
        } else {
            std::cerr << "Invalid file name" << std::endl;
        }
    }

    void load(employee::EmployeesArray &vars) {
        std::string file;
        std::cin >> file;
        std::ifstream out(file, std::ios::in);
        if (out) {
            out >> vars;
        } else {
            std::cerr << "Invalid file name" << std::endl;
        }
    }

}

int main() {
    std::string cmd;
    employee::EmployeesArray vars;

    while (std::cin) {
        std::cin >> cmd;
        if (cmd == "exit") {
            break;
        } else if (cmd == "list") {
            list(vars);
        } else if (cmd == "add") {
            add(vars);
        } else if (cmd == "save") {
            save(vars);
        } else if (cmd == "load") {
            load(vars);
        } else {
            return -1;
        }
    }
    return 0;
}
