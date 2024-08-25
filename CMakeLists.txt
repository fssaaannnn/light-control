cmake_minimum_required(VERSION 3.5.0)
project(light-control VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(platform/pwm)

include_directories(src)
include_directories(external)

include_directories(platform/pwm/src)

set(SOURCE_FILES
    external/httplib.cc
    src/main.cpp)

add_executable(light-control ${SOURCE_FILES})

target_link_libraries(light-control light-control-pwm-lib)

set(CMAKE_CXX_FLAGS_RELEASE "-Os")
