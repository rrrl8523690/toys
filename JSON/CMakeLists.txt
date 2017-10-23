cmake_minimum_required(VERSION 3.7)
project(JSON)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(SOURCE_FILES src/main.cpp src/JSON.cpp src/JSON.h src/JSONImpl.cpp src/JSONImpl.h test/JSONImplTest.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})