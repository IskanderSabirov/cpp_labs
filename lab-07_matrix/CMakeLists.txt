cmake_minimum_required(VERSION 3.16)
project(lab-07_matrix CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCES src/main.cpp src/matrix.cpp include/matrix.h )

add_executable(lab-07_matrix ${SOURCES})
include_directories(include)