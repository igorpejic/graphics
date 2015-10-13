
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

ADD_EXECUTABLE(p1 p1.cpp)
target_link_libraries(p1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
