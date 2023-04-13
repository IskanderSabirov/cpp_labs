#include <iostream>
#include <fstream>
#include "registers.h"

namespace my_registers {

    Registers::Registers(int size) {
        size_ = size;
        data_ = std::vector<my_matrix::Matrix>(10, my_matrix::Matrix());
    }

    void Registers::load(int reg, const std::string& file) {

        if (reg < 0 || reg > size_ - 1) {
            std::cout << "LOAD: invalid index of register. " << std::endl;
            return;
        }

        std::ifstream from(file, std::ios::out);
        if (!from)
            throw ::my_exception::MatrixException("LOAD: unable to open file.");

        int rows, cols;
        from >> rows;
        from >> cols;

        if (from.fail())
            throw ::my_exception::MatrixException("LOAD: invalid file format.");

        my_matrix::Matrix tmp(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                int val;
                from >> val;
                tmp.set(i, j, val);
            }

        if (from.fail())
            throw ::my_exception::MatrixException("LOAD: invalid file format.");

        data_[reg] = tmp;
    }

    void Registers::print(int reg) {
        if (reg < 0 || reg > size_ - 1) {
            std::cout << "PRINT: invalid index of register. " << std::endl;
            return;
        }
        std::cout << data_[reg];
    }

    void Registers::add(int reg1, int reg2) {
        if (reg1 < 0 || reg1 > size_ - 1 || reg2 < 0 || reg2 > size_ - 1) {
            std::cout << "PRINT: invalid index of register. " << std::endl;
            return;
        }
        data_[reg1] += data_[reg2];
    }

    void Registers::multiple(int reg1, int reg2) {
        if (reg1 < 0 || reg1 > size_ - 1 || reg2 < 0 || reg2 > size_ - 1) {
            std::cout << "MULTIPLE: invalid index of register. " << std::endl;
            return;
        }
        data_[reg1] *= data_[reg2];
    }

    void Registers::get_elem(int reg, int row, int col) {
        std::cout << data_[reg].get(row, col) << std::endl;
    }

}
