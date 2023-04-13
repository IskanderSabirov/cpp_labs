cmake_minimum_required(VERSION 3.16)
project(lab-06_int-vector CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCES src/main.cpp src/my_vector.cpp include/my_vector.hpp)

add_executable(lab-06_int-vector ${SOURCES})
include_directories(include)