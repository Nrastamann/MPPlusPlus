cmake_minimum_required(VERSION 4.0)

set (CMAKE_CXX_STANDARD 23)

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(MPPlusPlus)

set(SOURCE_EXE Tests.cpp)

set(SOURCE_LIB MPPlusPlus.cpp)

add_library(MPPlusPlus STATIC ${SOURCE_LIB})

add_executable(tests ${SOURCE_EXE})

target_link_libraries(tests MPPlusPlus)