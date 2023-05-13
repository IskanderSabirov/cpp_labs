cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME lab-14_linq)
set(COMMON_SOURCES include/linq.hpp )

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES1 tests/minimal_smoke_test.cpp ${COMMON_SOURCES})
set(MAIN_SOURCES2 tests/smoke_test.cpp ${COMMON_SOURCES})
set(MAIN_SOURCES src/test.cpp ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME}_minimal ${MAIN_SOURCES1})
add_executable(${X_PROJECT_NAME}_full ${MAIN_SOURCES2})
add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})

target_include_directories(${X_PROJECT_NAME}_minimal PRIVATE "include")
target_include_directories(${X_PROJECT_NAME}_full PRIVATE "include")
target_include_directories(${X_PROJECT_NAME} PRIVATE "include")

