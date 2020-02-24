cmake_minimum_required(VERSION 3.15)
project(grapito)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(grapito src/main.cpp src/listed_graph.h src/utils.h)