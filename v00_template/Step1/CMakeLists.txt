ADD_EXECUTABLE(Step1 Cone.cpp)
TARGET_LINK_LIBRARIES(Step1 vtkRendering)

########################################################
# add the install targets
install (TARGETS Step1 DESTINATION bin)
  
