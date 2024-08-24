cmake_minimum_required(VERSION 3.5.0)
project(light-control VERSION 0.1.0 LANGUAGES C CXX)

include_directories(./src)
include_directories(./external)

set(SOURCE_FILES
    external/httplib.cc
    src/main.cpp)

add_executable(light-control ${SOURCE_FILES})


