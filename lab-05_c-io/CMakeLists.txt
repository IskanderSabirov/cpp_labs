cmake_minimum_required(VERSION 3.16)
project(lab-05_c-io C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCES src/clist.c src/main.c src/point_list.c include/point_list.h include/clist.h)

add_executable(lab-05_c-io ${SOURCES})
include_directories(include)