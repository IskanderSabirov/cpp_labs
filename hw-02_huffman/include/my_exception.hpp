#ifndef HW_02_HUFFMAN_MY_EXCEPTION_HPP
#define HW_02_HUFFMAN_MY_EXCEPTION_HPP

#include <stdexcept>

namespace MyException {

    class my_exception : public std::runtime_error {

    public:

        explicit my_exception(const std::string &arg);

    };
}

#endif //HW_02_HUFFMAN_MY_EXCEPTION_HPP
