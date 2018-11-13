cmake_minimum_required(VERSION 3.12)

project(externals)

message("externals dir: " ${PROJECT_SOURCE_DIR})

#externals
add_subdirectory(${EXTERNALS_DIR}/glfw)
add_subdirectory(${EXTERNALS_DIR}/glm)
add_subdirectory(${EXTERNALS_DIR}/freetype2)