#include <fstream>
#include "doctest.h"
#include "binary_io.hpp"

using namespace BinaryIO;

///writer

TEST_CASE("write uint64_t test") {

std::ofstream file("../samples/write_test.txt", std::ios::binary);
auto w = writer(&file);
uint64_t n1 = 170;

w.write(n1, 8);
w.write_buffer();
file.close();
std::ifstream file1("../samples/write_test.txt", std::ios::binary);

int byte;
for (int i = 0; i < 8; i++) {
byte = file1.get();
CHECK_EQ(byte, (i == 7 ? 170 : 0));
}

byte = file1.get();
CHECK_EQ(byte, EOF);

}


TEST_CASE("write bit(bool) test") {

std::ofstream file("../samples/write_test.txt", std::ios::binary);
auto w = writer(&file);

for (int i = 0; i < 8; i++)
w.write(i % 2 == 0);
w.write_buffer();

file.close();

std::ifstream file1("../samples/write_test.txt", std::ios::binary);
CHECK_EQ(file1.get(), 170);

CHECK_EQ(file1.get(), EOF);
}


TEST_CASE("write char test") {

std::ofstream file("../samples/write_test.txt", std::ios::binary);
auto w = writer(&file);

for (int i = 0; i < 256; i++)
w.write(static_cast<char>(i));

file.close();

std::ifstream file1("../samples/write_test.txt", std::ios::binary);
for (int i = 0; i < 256; i++)
CHECK_EQ(i, file1.get());

CHECK_EQ(file1.get(), EOF);

}


TEST_CASE("write vector<bool> test") {

std::ofstream file("../samples/write_test.txt", std::ios::binary);
auto w = writer(&file);

auto v = std::vector<bool>{true, false, true, false, true, false, true, false};
w.write(v);
w.write_buffer();
file.close();

std::ifstream file1("../samples/write_test.txt", std::ios::binary);
CHECK_EQ(file1.get(), 170);

CHECK_EQ(file1.get(), EOF);
}

/// reader

TEST_CASE("read bit test") {

std::ofstream file("../samples/write_test.txt", std::ios::binary);
auto w = writer(&file);
for (int i = 0; i < 8; i++)
w.write(i % 2 == 0);
w.write_buffer();

file.close();

std::ifstream file1("../samples/write_test.txt", std::ios::binary);
auto r = reader(&file1);
for (int i = 0; i < 8; i++)
CHECK_EQ(r.read_bit(), (i % 2 == 0));

CHECK_THROWS(r.read_bit());

}


TEST_CASE("read bits test") {

std::ofstream file("../samples/write_test.txt", std::ios::binary);
auto w = writer(&file);
for (int i = 0; i < 8; i++)
w.write(i % 2 == 0);
w.write_buffer();

file.close();

std::ifstream file1("../samples/write_test.txt", std::ios::binary);
auto r = reader(&file1);

auto v1 = r.read_bits(8);
auto v = std::vector<bool>{true, false, true, false, true, false, true, false};

CHECK_EQ(v1, v);

CHECK_THROWS_WITH(r.read_bit(),"Error: can`t read new byte");
}


