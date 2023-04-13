cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME lab-08_shared-ptr)
set(COMMON_SOURCES src/matrix.cpp src/shared_ptr.cpp include/matrix.hpp include/shared_ptr.hpp)

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES src/main.cpp ${COMMON_SOURCES})
#set(TEST_SOURCES src/test.cpp ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
target_include_directories(${X_PROJECT_NAME} PRIVATE include)

#add_executable(${X_PROJECT_NAME}-test ${TEST_SOURCES})
#target_include_directories(${X_PROJECT_NAME}-test PRIVATE include)