cmake_minimum_required(VERSION 3.12)

project(common)

set(CMAKE_CXX_STANDARD 17)

message("common dir: " ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
        include/common/timer.h
        src/timer.cpp)

#includes
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})

#lib
add_library(${PROJECT_NAME} ${SOURCE_FILES})