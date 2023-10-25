cmake_minimum_required(VERSION 3.25)
project(Maze)

set(CMAKE_CXX_STANDARD 17)

add_library(MazeCreator maze_creator/maze_generator.cpp maze_creator/maze_generator.h)
target_include_directories(MazeCreator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/maze_creator)

add_library(Finder finder/finder.cpp finder/finder.h)
target_include_directories(Finder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/finder)

add_library(View STATIC
        view/view.h
        view/window.tpp
        view/field.cpp
        view/button.cpp
        view/window.h
        view/field.h
        view/button.h)

add_library(Controller INTERFACE controller/view_controller.h)
target_link_libraries(Controller INTERFACE View MazeCreator Finder)
target_link_directories(Controller INTERFACE controller)

target_link_libraries(View PRIVATE sfml-graphics sfml-window sfml-system Controller)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/SFML/include)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/view)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/finder)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes/SFML/include)
include_directories(${SFML_INCLUDE_DIR})
add_subdirectory(includes)

add_executable(Maze main.cpp)
target_link_libraries(Maze PRIVATE MazeCreator View Controller Finder)