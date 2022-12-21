cmake_minimum_required(VERSION 3.16)
project(hw-01_bmp C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCES src/main.c src/bmp_helper.c include/bmp_helper.h)

add_executable(hw-01_bmp ${SOURCES})
include_directories(include)