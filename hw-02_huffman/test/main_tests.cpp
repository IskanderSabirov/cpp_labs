#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "decoding.hpp"
#include "encoding.hpp"

namespace {

    bool is_equal_files(const std::string &n1, const std::string &n2) {
        std::ifstream file1(n1, std::ios::binary);
        std::ifstream file2(n2, std::ios::binary);
        if (file1.tellg() != file2.tellg())
            return false;

        int symbol1, symbol2;
        symbol1 = file1.get();
        symbol2 = file2.get();

        while (symbol1 != EOF && symbol2 != EOF) {
            if (symbol1 != symbol2)
                return false;
            symbol1 = file1.get();
            symbol2 = file2.get();
        }
        return true;
    }

    void code(const std::string &n1, const std::string &n2) {
        std::ifstream from(n1, std::ios::binary);
        std::ofstream to(n2, std::ios::binary);
        auto encoder = MyEncoder::encoder(&from, &to);
        encoder.write();
        from.close();
        to.close();
    }

    void decode(const std::string &n2, const std::string &n3) {
        std::ifstream from(n2, std::ios::binary);
        std::ofstream to(n3, std::ios::binary);
        auto decoder = MyDecoder::decoder(&from, &to);
        decoder.write_text();
        from.close();
        to.close();
    }

    bool do_code_decode(const std::string &n1, const std::string &n2, const std::string &n3) {
        try {
            code(n1, n2);
            decode(n2, n3);
        } catch (MyException::my_exception &e) {
            std::cout << e.what() << std::endl;
            return false;
        }
        return is_equal_files(n1, n3);
    }

    void write_all_chars(const std::string &n1) {
        std::ofstream out(n1, std::ios::binary);
        for (int i = 0; i < 256; i++) {
            out << (unsigned char) i;
        }
    }

}

TEST_CASE("Encoding/decoding test - empty file ") {
    CHECK_EQ(do_code_decode("../samples/from1.txt", "../samples/code1.txt", "../samples/to1.txt"), true);
}

TEST_CASE("Encoding/decoding test - all chars ") {
    write_all_chars("../samples/from2.txt");
    CHECK_EQ(do_code_decode("../samples/from2.txt", "../samples/code2.txt", "../samples/to2.txt"), true);
}

TEST_CASE("Encoding/decoding test - Lena ") {
    CHECK_EQ(do_code_decode("../samples/lena_512.bmp", "../samples/code_lena.txt", "../samples/lena.bmp"), true);
}



