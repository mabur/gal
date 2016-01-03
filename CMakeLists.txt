# Top-Level CMakeList.txt
cmake_minimum_required(VERSION 3.4)
enable_language(CXX)
add_definitions(-std=c++11)

include_directories(include)
file(GLOB gal_header_files "include/*.hpp")

PROJECT(gal)
add_executable(test_gal tests/main.cpp ${gal_header_files})
