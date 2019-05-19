cmake_minimum_required(VERSION 3.6.0)

project(sorting VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE PROJECT_SOURCES
    "*.h"
    "*.hpp"
    "*.cpp"
)

find_package (Threads)

list(FILTER PROJECT_SOURCES EXCLUDE REGEX "builds.*")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
