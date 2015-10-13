ADD_EXECUTABLE(Step2 Cone.cpp)
TARGET_LINK_LIBRARIES(Step2 vtkRendering)

########################################################
# add the install targets
install (TARGETS Step2 DESTINATION bin)
