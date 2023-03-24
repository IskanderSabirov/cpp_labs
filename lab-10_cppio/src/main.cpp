#include <fstream>
#include "employees.h"

int main() {
    std::string cmd;
    EmployeesArray vars;

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
                auto *e = new Developer();
                std::cin >> *(Employee *) e;
                vars.add((Employee *) e);
            } else {
                auto e = new SalesManager();
                std::cin >> *(Employee *) e;
                vars.add((Employee *) e);
            }
        } else if (cmd == "save") {
            std::string file;
            std::cin >> file;
            std::ofstream out;                      // поток для чтения
            out.open(file, std::ios::out); // открываем файл для чтения
            if (out.is_open()) {                    //если файл открыт
                out << vars;
                out.close();
            } else {
                std::cerr << "Invalid file name" << std::endl;
            }
        } else {
            return -1;
        }
    }


    return 0;
}
