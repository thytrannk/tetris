cmake_minimum_required(VERSION 3.12)
project(tetris)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

include_directories($ENV{PROJECT_HOME}/glad/include)
link_directories($ENV{PROJECT_HOME}/glad/include)

find_library(FREEIMAGE_LIBRARY freeimage)
include_directories(freeimage)

include_directories($ENV{PROJECT_HOME}/irrKlang-1.6.0/include)
link_directories($ENV{PROJECT_HOME}/irrKlang-1.6.0/include)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_INCLUDE_DIRS})

add_executable(tetris main.cpp main.h
        glad.c shader.h
        pieces.cpp pieces.h
        board.cpp board.h
        game.cpp game.h
        display.cpp display.h global.h)

target_link_libraries(tetris freeimage)
target_link_libraries(tetris ${GLFW_LIBRARIES})
target_link_libraries(tetris ${GLFW_STATIC_LIBRARIES})
target_link_libraries(tetris ${CMAKE_SOURCE_DIR}/libirrklang.dylib)

#