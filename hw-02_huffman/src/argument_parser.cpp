#include <cstring>
#include "argument_parser.hpp"
#include "my_exception.hpp"

//#define equals(s1, s2) strcmp(s1,s2)

namespace MyParser {
    parser::parser(int argc, char *argv[]) {

        if (argc != 6)
            throw MyException::my_exception("Error: wrong args count");


        to_file_ = "";
        from_file_ = "";
        operation_type_ = '-';

        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-c") == 0)
                operation_type_ = 'c';
            else if (strcmp(argv[i], "-u") == 0)
                operation_type_ = 'u';
            else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
                from_file_ = argv[++i];
            else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
                to_file_ = argv[++i];
            else
                throw MyException::my_exception("Error: invalid argument type");
        }

        if (to_file_.empty() || from_file_.empty() || operation_type_ == '-')
            throw MyException::my_exception("Error: not all arguments given");

    }

    const std::string &parser::get_from_file() const noexcept {
        return from_file_;
    }

    const std::string &parser::get_to_file() const noexcept {
        return to_file_;
    }

    const char &parser::get_operation_type_() const noexcept {
        return operation_type_;
    }
}