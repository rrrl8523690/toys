cmake_minimum_required(VERSION 3.7)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/ThreadPool.cpp src/ThreadPool.h)
add_executable(ThreadPool ${SOURCE_FILES})