cmake_minimum_required(VERSION 2.6)
project(OGL_Teksture)

set(DATA_FOLDER "${PROJECT_SOURCE_DIR}/data/")

configure_file (
  "${PROJECT_SOURCE_DIR}/pathconfig.h.in"
  "${PROJECT_BINARY_DIR}/pathconfig.h"
  )

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

find_package(GLUT)
find_package(OpenGL)

cmake_minimum_required(VERSION 2.6)
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})

add_executable(glt_01 imageloader.cpp imageloader.h v08.cpp)
target_link_libraries(glt_01 ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
