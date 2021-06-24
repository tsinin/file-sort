cmake_minimum_required(VERSION 3.16)
project(file_sort)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(file_sort main.cpp src/file_generation.h src/file_generation.cpp src/file_sorting.h src/file_sorting.cpp)