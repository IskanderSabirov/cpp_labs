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
            std::ofstream out;                       // поток для чтения
            out.open(file, std::ios::out);  // открываем файл для записи
            if (out) {                              //если файл открыт
                out << vars;
                out.close();
            } else {
                std::cerr << "Invalid file name" << std::endl;
            }
        } else if (cmd == "load") {
            std::string file;
            std::cin >> file;
            std::ifstream out;                       // поток для чтения
            out.open(file, std::ios::in);  // открываем файл для чтения
            if (out) {                              //если файл открыт
                out >> vars;
                out.close();
            } else {
                std::cerr << "Invalid file name" << std::endl;
            }
        } else {
            return -1;
        }
    }

//    std::ifstream instrm("..\\example.edb", std::ios::binary);
//    for(int i = 0; i < 8; i ++){
//        if(i==3){
//            bool b;
//            instrm >> read_bool(&b);
//            std::cout << b << ' ';
//        }else{
//            int a = 0;
//            (instrm >> read_le_int32(&a));
//            std::cout << a << ' ';
//        }
//    }

//    int a = 0;
    // читаем числа по одному из файла и выводим
//    while (instrm >> read_le_int32(&a))
//        std::cout << a << ' ';
//    std::cout << '\n';
//    instrm >> read_le_int32(&a);
    return 0;
}
