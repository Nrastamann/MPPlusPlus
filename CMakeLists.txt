cmake_minimum_required(VERSION 4.0)

project(MPPlusPlus)

set(SOURCE_EXE Tests.cpp)

set(SOURCE_LIB MPPlusPlus.cpp)

add_library(MPPlusPlus STATIC ${SOURCE_LIB})

add_executable(tests ${SOURCE_EXE})

target_compile_features(tests PUBLIC cxx_std_23)

target_link_libraries(tests MPPlusPlus)