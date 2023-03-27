#include <fstream>
#include "employees.h"

int main() {
    std::string cmd;
    employee::EmployeesArray vars;

    while (std::cin) {
        std::cin >> cmd;
        if (cmd == "exit") {
            break;
        } else if (cmd == "list") {
            std::cout << vars << std::endl;
        } else if (cmd == "add") {
            int32_t type;
            std::cin >> type;
            if (type != 1 && type != 2)
                std::cerr << "Invalid type of worker, only 1 and 2" << std::endl;
            if (type == 1) {
                auto e = new employee::Developer();
                std::cin >> *(employee::Employee *) e;
                vars.add((employee::Employee *) e);
            } else {
                auto e = new employee::SalesManager();
                std::cin >> *(employee::Employee *) e;
                vars.add((employee::Employee *) e);
            }
        } else if (cmd == "save") {
            std::string file;
            std::cin >> file;
            std::ofstream out(file, std::ios::out);
            if (out) {
                out << vars;
            } else {
                std::cerr << "Invalid file name" << std::endl;
            }
        } else if (cmd == "load") {
            std::string file;
            std::cin >> file;
            std::ifstream out(file, std::ios::in);
            if (out) {
                out >> vars;
            } else {
                std::cerr << "Invalid file name" << std::endl;
            }
        } else {
            return -1;
        }
    }
    return 0;
}
