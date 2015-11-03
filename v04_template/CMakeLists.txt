PROJECT (v04)

cmake_minimum_required(VERSION 2.6)
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pedantic")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

ADD_EXECUTABLE(p1 p1.cpp)
target_link_libraries(p1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
