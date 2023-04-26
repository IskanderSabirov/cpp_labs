#include <fstream>
#include "doctest.h"
#include "encoding.hpp"

using namespace MyEncoder;

TEST_CASE("test - encoding with from3.txt") {
    std::ifstream from("../samples/from3.txt", std::ios::binary);
    std::ofstream to("../samples/code3.txt", std::ios::binary);

    auto e = encoder(&from, &to);

    e.write();

    CHECK_EQ(e.get_header_length(), 16 + 3 + 1 + 3);
    CHECK_EQ(e.get_encoded_text_length(), 2);
    CHECK_EQ(e.get_read_text_length(), 9);

}

TEST_CASE("test - encoding with empty from1.tx") {
    std::ifstream from("../samples/from1.txt", std::ios::binary);
    std::ofstream to("../samples/code1.txt", std::ios::binary);

    auto e = encoder(&from, &to);

    e.write();

    CHECK_EQ(e.get_header_length(), 17);
    CHECK_EQ(e.get_encoded_text_length(), 0);
    CHECK_EQ(e.get_read_text_length(), 0);

}

TEST_CASE("test - encoding with all chars from2.tx") {
    std::ifstream from("../samples/from2.txt", std::ios::binary);
    std::ofstream to("../samples/code2.txt", std::ios::binary);

    auto e = encoder(&from, &to);

    e.write();

    CHECK_EQ(e.get_read_text_length(), 256);

}