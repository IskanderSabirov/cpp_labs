#include "registers.h"


namespace {
    int get_register_number() {
        std::string val;
        std::cin >> val;
        if(val.size()!=2)
            throw my_exception::MatrixException("Error: invalid register number");
        return val[1] - '0';
    }
}

int main() {
    std::string cmd;
    my_registers::Registers registers(10);

    while (std::cin) {
        std::cin >> cmd;
        try {
            if (cmd == "exit") {
                break;
            } else if (cmd == "load") {
                int reg = get_register_number();
                std::string file;
                std::cin >> file;
                registers.load(reg, file);
            } else if (cmd == "print") {
                int reg = get_register_number();
                registers.print(reg);
            } else if (cmd == "add") {
                int reg1 = get_register_number();
                int reg2 = get_register_number();
                registers.add(reg1, reg2);
            } else if (cmd == "mul") {
                int reg1 = get_register_number();
                int reg2 = get_register_number();
                registers.multiple(reg1, reg2);
            } else if (cmd == "elem") {
                int reg = get_register_number();
                int row, col;
                std::cin >> row >> col;
                registers.get_elem(reg, row, col);
            } else {
                return -1;
            }
        } catch (my_exception::MatrixException &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}