cmake_minimum_required(VERSION 3.7)
project(toys)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        JSON/src/JSON.cpp
        JSON/include/JSON.h
        JSON/src/JSONImpl.cpp
        JSON/include/JSONImpl.h
        JSON/test/JSONImplTest.h
        JSON/CMakeLists.txt
        Test/src/Test.cpp
        Test/src/Test.h
        Test/CMakeLists.txt
        ThreadPool/src/ThreadPool.cpp
        ThreadPool/src/ThreadPool.h
        ThreadPool/CMakeLists.txt)

include_directories(JSON/include)
include_directories(Test/src)
include_directories(ThreadPool/src)

add_executable(JSONTest ${SOURCE_FILES} JSON/include/JSONTraits.h JSON/test/RunTest.cpp)
add_library(toys SHARED ${SOURCE_FILES})
