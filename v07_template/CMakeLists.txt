cmake_minimum_required(VERSION 2.6)
project(lights)

find_package(GLUT)
find_package(OpenGL)

include_directories(${CMAKE_SOURCE_DIR})

include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})

add_executable(gl_light gl_light.cpp)
target_link_libraries(gl_light ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
