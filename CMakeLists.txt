cmake_minimum_required(VERSION 3.15)
project(run_trump_local)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)

add_executable(run_trump_local main.cpp)

target_link_libraries(run_trump_local ${SDL2_LIBRARIES})