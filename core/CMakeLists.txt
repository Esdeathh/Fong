cmake_minimum_required(VERSION 3.12)

project(core)

set(CMAKE_CXX_STANDARD 17)

message("core dir: " ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
        include/core/Window.h
        include/core/Application.h
        src/Application.cpp
        src/Window.cpp)

#includes
include_directories(${PROJECT_SOURCE_DIR}/include/core)

#lib
add_library(${PROJECT_NAME} ${SOURCE_FILES} ${EXTERNALS_DIR}/glad/src/glad.c)

#Add targets
target_link_libraries(${PROJECT_NAME} glm glfw common)