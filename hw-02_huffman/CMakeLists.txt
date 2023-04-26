cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME hw-02_huffman)
set(COMMON_SOURCES
        "include/node.hpp" src/node.cpp "include/encoding.hpp" src/encoding.cpp "include/my_exception.hpp"
        src/my_exception.cpp src/argument_parser.cpp "include/argument_parser.hpp" "include/binary_io.hpp"
        src/binary_io.cpp "include/tree.hpp" src/tree.cpp src/decoding.cpp "include/decoding.hpp")

set(TEST_SOURCES "include/doctest.h" "test/parser_tests.cpp" "test/binary_io_tests.cpp" "test/tree_tests.cpp"
        "test/decoding_tests.cpp" "test/encoding_tests.cpp")

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES src/main.cpp ${COMMON_SOURCES})
set(TEST_SOURCES "test/main_tests.cpp" ${TEST_SOURCES} ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
add_executable(${X_PROJECT_NAME}_test ${TEST_SOURCES})

target_include_directories(${X_PROJECT_NAME} PRIVATE "include")
target_include_directories(${X_PROJECT_NAME}_test PRIVATE "include")


