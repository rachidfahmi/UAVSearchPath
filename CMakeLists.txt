cmake_minimum_required(VERSION 3.19)
project(UAVSearchPath)

if(NOT DEFINED ENV{CADMIUM})
    message(FATAL_ERROR
        "CADMIUM environment variable is not set.\n"
        "Please run: export CADMIUM=~/cadmium_v2/include")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories($ENV{CADMIUM})
include_directories($ENV{CADMIUM}/../json/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/main/include)

add_executable(UAVSearch main/main.cpp)