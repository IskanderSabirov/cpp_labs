cmake_minimum_required(VERSION 3.16)
project(lab-03_mergesort C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCES src/main.c src/mergesort.c include/mergesort.h )

add_executable(lab-03_mergesort ${SOURCES})
target_include_directories(lab-03_mergesort PRIVATE include)