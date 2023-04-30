#include <fstream>
#include "doctest.h"
#include "decoding.hpp"

using namespace MyDecoder;

TEST_CASE("test - work with empty file") {

    std::ifstream from1("../samples/code1.txt", std::ios::binary);
    std::ofstream to1("../samples/to1.txt", std::ios::binary);
    auto d1 = decoder(&from1, &to1);

    CHECK_EQ(d1.get_header_length(), 17);
    CHECK_EQ(d1.get_not_codded_text_length(), 0);
    CHECK_EQ(d1.get_codded_length(), 0);

}

TEST_CASE("test - work with all chars") {

    std::ifstream from2("../samples/code2.txt", std::ios::binary);
    std::ofstream to2("../samples/to2.txt", std::ios::binary);
    auto d2 = decoder(&from2, &to2);


    CHECK_EQ(d2.get_not_codded_text_length(), 256);

}

TEST_CASE("test - work with from3.txt") {

    std::ifstream from2("../samples/code3.txt", std::ios::binary);
    std::ofstream to2("../samples/to3.txt", std::ios::binary);
    auto d2 = decoder(&from2, &to2);


    CHECK_EQ(d2.get_not_codded_text_length(), 9);
    CHECK_EQ(d2.get_header_length(), 23);
    CHECK_EQ(d2.get_codded_length(), 2);

}