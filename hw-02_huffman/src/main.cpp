#include <iostream>
#include <fstream>
#include "argument_parser.hpp"
#include "encoding.hpp"
#include "decoding.hpp"

int main(int argc, char *argv[]) {

    try {
        auto parser = MyParser::parser(argc, argv);

        auto from = std::ifstream(parser.get_from_file(), std::ios::binary);
        auto to = std::ofstream(parser.get_to_file(), std::ios::binary);

        if (!from.is_open() || !to.is_open())
            throw MyException::my_exception("Error: file does not exist");

        if (parser.get_operation_type_() == 'u') {

            auto decoder = MyDecoder::decoder(&from, &to);
            decoder.write_text();
            std::cout << decoder;

        } else {

            auto encoder = MyEncoder::encoder(&from, &to);
            encoder.write();
            std::cout << encoder;

        }

    } catch (MyException::my_exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}