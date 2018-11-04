cmake_minimum_required(VERSION 3.12)
project(Fong)

set(EXTERNALS_DIR ${PROJECT_SOURCE_DIR}/externals)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

find_package(OpenGL REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
message("${PROJECT_SOURCE_DIR}/")

include_directories("${EXTERNALS_DIR}")
include_directories("${EXTERNALS_DIR}/glad/include")
include_directories("${EXTERNALS_DIR}/glfw/include")
include_directories("${EXTERNALS_DIR}/glm/glm")

#externals
add_subdirectory(${EXTERNALS_DIR}/glfw)
add_subdirectory(${EXTERNALS_DIR}/glm)

set(SOURCE_FILES
        main.cpp
        src/Application.cpp
        src/Window.cpp
        ${EXTERNALS_DIR}/glad/src/glad.c)

add_executable(Fong ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} glm glfw)