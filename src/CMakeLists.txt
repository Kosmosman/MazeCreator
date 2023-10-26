cmake_minimum_required(VERSION 3.15)
project(Maze)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(MazeCreator model/maze_creator/maze_generator.cpp model/maze_creator/maze_generator.h)
target_include_directories(MazeCreator PUBLIC model/maze_creator)
target_include_directories(MazeCreator PUBLIC model/randomizer)

add_library(Finder model/finder/finder.cpp model/finder/finder.h)
target_include_directories(Finder PUBLIC model/finder)

add_library(Validator INTERFACE model/validator/validator.h)
target_include_directories(Validator INTERFACE model/validator)

add_library(View STATIC
        view/facade.h
        view/view.h
        view/window.tpp
        view/field.cpp
        view/button.cpp
        view/window.h
        view/field.h
        view/button.h)

add_library(Controller INTERFACE controller/controller.h)
target_link_libraries(Controller INTERFACE MazeCreator Finder Validator)
target_link_directories(Controller INTERFACE controller)

set(FONT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/view/font)
include_directories(${FONT_DIR})


target_link_libraries(View PRIVATE sfml-graphics sfml-window sfml-system Controller)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/SFML/include)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/view)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes/SFML/include)
include_directories(${SFML_INCLUDE_DIR})
add_subdirectory(includes)

add_executable(Maze main.cpp)
target_link_libraries(Maze PRIVATE MazeCreator View Controller Finder)

enable_testing()
add_executable(Test test/test.cpp)
target_include_directories(Test PRIVATE test)
target_include_directories(Test PRIVATE controller)
target_link_libraries(Test PRIVATE Finder Controller GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(Test)