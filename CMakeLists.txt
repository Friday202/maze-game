cmake_minimum_required(VERSION 3.9)

project(maze-game)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRCS "src/*.cpp") 

add_executable(${PROJECT_NAME} main.cpp ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE src/)