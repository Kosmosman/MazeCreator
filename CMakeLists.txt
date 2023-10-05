cmake_minimum_required(VERSION 3.25)
project(Maze)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/maze_creator)

add_executable(Maze
        src/maze_creator/maze_generator.cpp
        src/maze_creator/maze_generator.h
        src/main.cpp src/randomizer/randomizer.h)
