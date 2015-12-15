cmake_minimum_required(VERSION 2.6)
project(lights)

find_package(GLUT)
find_package(OpenGL)

find_package(VTK REQUIRED)

include(${VTK_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR})

include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})

add_executable(p01 p01.cpp)
target_link_libraries(p01 ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
