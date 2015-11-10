PROJECT (v05)

cmake_minimum_required(VERSION 2.6)
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pedantic")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/eigen-3.2.6/")
#set(Eigen3_DIR "${PROJECT_SOURCE_DIR}/eigen-3.2.6/")
#find_package( Eigen3  REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(p1 p1.cpp )
target_link_libraries(p1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
