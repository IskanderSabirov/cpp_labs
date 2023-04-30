#include "argument_parser.hpp"
#include "doctest.h"

using namespace MyParser;

TEST_CASE("parser tests  - correct flags") {
    char *command1 = (char *) "-c";
    char *command2 = (char *) "-u";
    char *file1 = (char *) "-f";
    char *file2 = (char *) "--file";
    char *from = (char *) "../samples/from1.txt";
    char *out_file1 = (char *) "-o";
    char *out_file2 = (char *) "--output";
    char *to = (char *) "../samples/to1.txt";

    char *argv[] = {nullptr, command1, file1, from, out_file1, to};
    int argc = 6;
    auto p = parser(argc, argv);

    CHECK_EQ(p.get_to_file(), "../samples/to1.txt");
    CHECK_EQ(p.get_from_file(), "../samples/from1.txt");
    CHECK_EQ(p.get_operation_type_(), 'c');

    char *argv1[] = {nullptr, file2, from, out_file2, to, command2};
    int argc1 = 6;
    auto p1 = parser(argc1, argv1);

    CHECK_EQ(p1.get_to_file(), "../samples/to1.txt");
    CHECK_EQ(p1.get_from_file(), "../samples/from1.txt");
    CHECK_EQ(p1.get_operation_type_(), 'u');


    char *argv3[] = {nullptr, out_file2, to, command2, file2, from};
    int argc3 = 6;
    auto p3 = parser(argc3, argv3);

    CHECK_EQ(p3.get_to_file(), "../samples/to1.txt");
    CHECK_EQ(p3.get_from_file(), "../samples/from1.txt");
    CHECK_EQ(p3.get_operation_type_(), 'u');

}

TEST_CASE("parser tests  - incorrect flags") {
    char *command1 = (char *) "-c";
    char *command2 = (char *) "-u";
    char *file1 = (char *) "-f";
    char *file2 = (char *) "--file";
    char *from = (char *) "../samples/from1.txt";
    char *out_file1 = (char *) "-o";
    char *out_file2 = (char *) "--output";
    char *to = (char *) "../samples/to1.txt";

    char *argv[] = {nullptr, command1, file1, from, out_file1, to};
    int argc = 7;
    CHECK_THROWS_WITH(parser(argc, argv), "Error: wrong args count");

    char *argv1[] = {nullptr, command2, command1, out_file2, to, command2};
    int argc1 = 6;
    CHECK_THROWS_WITH (parser(argc1, argv1), "Error: not all arguments given");

    char *argv2[] = {nullptr, file2, out_file1, from, to, command2};
    int argc2 = 6;
    CHECK_THROWS_WITH (parser(argc2, argv2), "Error: invalid argument type");


}