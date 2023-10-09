cmake_minimum_required(VERSION 3.25)
project(Maze)

set(CMAKE_CXX_STANDARD 17)

add_library(MazeCreator maze_creator/maze_generator.cpp maze_creator/maze_generator.h)
target_include_directories(MazeCreator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/maze_creator)

add_library(View STATIC
        view/window.cpp
        view/field.cpp
        view/buttons.cpp
        view/window.h
        view/field.h
        view/buttons.h)

target_link_libraries(View PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/SFML/include)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/view)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes/SFML/include)
include_directories(${SFML_INCLUDE_DIR})
add_subdirectory(includes)

add_executable(Maze main.cpp)
target_link_libraries(Maze PRIVATE MazeCreator View)