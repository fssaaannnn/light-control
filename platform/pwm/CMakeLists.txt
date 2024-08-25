cmake_minimum_required(VERSION 3.5.0)
project(light-control-pwm-lib VERSION 0.1.0 LANGUAGES C CXX)

set(LC_BUILD_ENV_RPI "Raspberry Pi")
execute_process(COMMAND grep --binary-files=text -o ${LC_BUILD_ENV_RPI} /proc/device-tree/model 
                COMMAND tr -d '\n'
                OUTPUT_VARIABLE LC_BUILD_ENV ERROR_VARIABLE LC_BUILD_ENV_ERR)
message(STATUS "LC_BUILD_ENV: ${LC_BUILD_ENV}")

if(LC_BUILD_ENV STREQUAL ${LC_BUILD_ENV_RPI})
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
    find_package(pigpio)
    include_directories(${pigpio_INCLUDE_DIR})
    add_compile_definitions(LC_PIGPIO_AVAILABLE_ENV)
else()
    message(WARNING "pigpio is not available in this environment")
endif()


include_directories(src)

set(SOURCE_FILES
        src/PwmControl.cpp
        src/NullPwmControl.cpp
        src/PigpioPwmControl.cpp)

add_library(light-control-pwm-lib STATIC ${SOURCE_FILES})

if(LC_BUILD_ENV STREQUAL ${LC_BUILD_ENV_RPI})
    target_link_libraries(light-control-pwm-lib ${pigpio_LIBRARY})
endif()
