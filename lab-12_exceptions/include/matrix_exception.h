#ifndef LAB_12_EXCEPTIONS_MATRIX_EXCEPTION_HPP
#define LAB_12_EXCEPTIONS_MATRIX_EXCEPTION_HPP

#include <stdexcept>

namespace my_exception {

    class MatrixException : public std::runtime_error {

    public:

        explicit MatrixException(const std::string &arg);

    };
}

#endif //LAB_12_EXCEPTIONS_MATRIX_EXCEPTION_HPP
