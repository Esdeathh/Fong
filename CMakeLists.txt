cmake_minimum_required(VERSION 3.12)
project(Fong)

set(EXTERNALS_DIR ${PROJECT_SOURCE_DIR}/externals)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

find_package(OpenGL REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}")
message("${PROJECT_SOURCE_DIR}/")

include_directories("${EXTERNALS_DIR}")
include_directories("${EXTERNALS_DIR}/glad/include")
include_directories("${EXTERNALS_DIR}/glfw/include")
include_directories("${EXTERNALS_DIR}/glm/glm")

#externals
add_subdirectory(${EXTERNALS_DIR}/glfw)
add_subdirectory(${EXTERNALS_DIR}/glm)

add_executable(Fong main.cpp)