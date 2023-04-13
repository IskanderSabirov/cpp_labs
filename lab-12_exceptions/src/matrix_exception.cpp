#include "matrix_exception.h"

namespace my_exception {

    MatrixException::MatrixException(const std::string &arg) : runtime_error(arg) {};

}