cmake_minimum_required(VERSION 3.7)
project(JSON)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES src/JSON.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(JSONTest ${SOURCE_FILES} test/RunTest.cpp)