find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

ADD_EXECUTABLE(p2 p2.cpp)
if(VTK_LIBRARIES)
  target_link_libraries(p2 ${VTK_LIBRARIES})
else()
  target_link_libraries(p2 vtkHybrid)
endif()
