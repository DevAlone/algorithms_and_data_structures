cmake_minimum_required(VERSION 3.0.0)

project(sorting VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE PROJECT_SOURCES
    "*.h"
    "*.hpp"
    "*.cpp"
)

find_package(Qt5Core)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
