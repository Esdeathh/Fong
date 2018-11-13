cmake_minimum_required(VERSION 3.12)
project(Fong)

set(EXTERNALS_DIR ${PROJECT_SOURCE_DIR}/externals)
set(COMMON_DIR ${PROJECT_SOURCE_DIR}/common)

set(CMAKE_CXX_STANDARD 17)

message("Fong dir: " ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES main.cpp)

#includes
include(GNUInstallDirs)

include_directories("${PROJECT_SOURCE_DIR}/core/include")
include_directories(${EXTERNALS_DIR}/glad/include)
include_directories(${EXTERNALS_DIR}/stb_image/include)
include_directories(${EXTERNALS_DIR}/glfw/include)
include_directories(${EXTERNALS_DIR}/glm/glm)
include_directories(${EXTERNALS_DIR}/freetype2/include)
include_directories(${COMMON_DIR}/include)

#subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/externals)
add_subdirectory(${PROJECT_SOURCE_DIR}/common)
add_subdirectory(${PROJECT_SOURCE_DIR}/core)

#exec
add_executable(Fong ${SOURCE_FILES})

#Setup OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

#Add targets
target_link_libraries(${PROJECT_NAME} core)