cmake_minimum_required(VERSION 3.16)
project(lab-04_intrusive-list C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCES src/clist.c src/main.c include/clist.h)

add_executable(lab-04_intrusive-list ${SOURCES})
include_directories(include)