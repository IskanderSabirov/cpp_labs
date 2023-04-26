#ifndef HW_02_HUFFMAN_ARGUMENT_PARSER_HPP
#define HW_02_HUFFMAN_ARGUMENT_PARSER_HPP

#include <string>

namespace MyParser {

    class parser {
    private:
        std::string to_file_;
        std::string from_file_;
        char operation_type_;
    public:
        parser(int argc, char *argv[]);

        [[nodiscard]] const std::string &get_from_file() const noexcept;

        [[nodiscard]] const std::string &get_to_file() const noexcept;

        [[nodiscard]] const char &get_operation_type_() const noexcept;
    };

}

#endif //HW_02_HUFFMAN_ARGUMENT_PARSER_HPP
