cmake_minimum_required(VERSION 3.6)
project(maze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MazeBuilder.cpp MazeBuilder.hpp RandomCellList.hpp)
add_executable(maze ${SOURCE_FILES})