cmake_minimum_required(VERSION 2.6)
project(Konture)


add_definitions(-std=c++0x )
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

find_package(GLUT)
find_package(OpenGL)

cmake_minimum_required(VERSION 2.6)
include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})

add_executable(kontura main.cpp )
target_link_libraries(kontura ${GLUT_LIBRARY} ${OPENGL_LIBRARY})


