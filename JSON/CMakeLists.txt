cmake_minimum_required(VERSION 3.7)
project(JSON)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/JSON.cpp src/JSON.h src/JSONValue.cpp src/JSONValue.h)
add_executable(JSON ${SOURCE_FILES})