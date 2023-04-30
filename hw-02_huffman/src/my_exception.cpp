#include "my_exception.hpp"

namespace MyException {

    my_exception::my_exception(const std::string &arg) : runtime_error(arg) {};

}