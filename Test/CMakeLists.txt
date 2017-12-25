cmake_minimum_required(VERSION 3.7)
project(Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Test.cpp src/Test.h)
add_executable(Test ${SOURCE_FILES})