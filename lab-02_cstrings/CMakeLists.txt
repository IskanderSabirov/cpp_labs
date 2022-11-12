cmake_minimum_required(VERSION 3.16)
project(lab-02_cstrings C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCES src/str.c src/test.c src/test_str.c include/str.h include/test_str.h )

add_executable(lab-02_cstrings ${SOURCES})
target_include_directories(lab-02_cstrings PRIVATE include)