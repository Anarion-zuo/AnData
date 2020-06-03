cmake_minimum_required(VERSION 3.16)
project(AnData)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
include_directories(include)
include_directories(include/base)

add_executable(AnData main.cpp)
target_link_libraries(AnData anariondata)