cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project("SimpleValidator")
add_executable(validator main.cpp)
add_executable(checker checker.cpp)
