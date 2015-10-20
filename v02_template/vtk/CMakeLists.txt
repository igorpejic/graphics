find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(DATA_FOLDER "${PROJECT_SOURCE_DIR}/data" CACHE PATH "data location")

configure_file (
  "${PROJECT_SOURCE_DIR}/vtk/pathconfig.h.in"
  "${PROJECT_BINARY_DIR}/pathconfig.h"
  )
include_directories(${PROJECT_BINARY_DIR})

ADD_EXECUTABLE(p2 p2.cpp)
if(VTK_LIBRARIES)
  target_link_libraries(p2 ${VTK_LIBRARIES})
else()
  target_link_libraries(p2 vtkHybrid)
endif()
