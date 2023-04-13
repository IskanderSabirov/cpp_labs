#ifndef LAB_12_EXCEPTIONS_REGISTERS_HPP
#define LAB_12_EXCEPTIONS_REGISTERS_HPP

#include <string>
#include <vector>
#include "matrix.h"

namespace my_registers {

    class Registers {

    public:

        explicit Registers(int size);

        void load(int reg, const std::string& file);

        void print(int reg);

        void add(int reg1, int reg2);

        void multiple(int reg1, int reg2);

        void get_elem(int reg, int row, int col);

    private:
        std::vector<my_matrix::Matrix> data_;
        int size_;
    };
}

#endif //LAB_12_EXCEPTIONS_REGISTERS_HPP
