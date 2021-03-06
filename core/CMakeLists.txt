cmake_minimum_required(VERSION 3.12)

project(core)

set(CMAKE_CXX_STANDARD 17)

message("core dir: " ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
        src/Application.cpp
        src/Window.cpp
        src/VertexArray.cpp
        src/VertexBuffer.cpp
        src/IndexBuffer.cpp
        src/Shader.cpp
        src/Texture.cpp
        src/Mesh.cpp
        src/Rectangle.cpp
        src/Circle.cpp
        src/Font.cpp src/Player.cpp src/Player.h)

#includes
include_directories(${PROJECT_SOURCE_DIR}/include/core)

#lib
add_library(${PROJECT_NAME} ${SOURCE_FILES} ${EXTERNALS_DIR}/glad/src/glad.c
                                            ${EXTERNALS_DIR}/stb_image/src/stb_image.cpp)

#Add targets
target_link_libraries(${PROJECT_NAME} glm glfw common freetype)