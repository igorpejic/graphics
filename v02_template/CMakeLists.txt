PROJECT (v02)

cmake_minimum_required(VERSION 2.6)
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pedantic")
add_subdirectory(gl)
add_subdirectory(vtk)
