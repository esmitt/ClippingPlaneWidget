cmake_minimum_required(VERSION 2.8)
 
PROJECT(ClippingPlaneWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ClippingPlaneWidget MACOSX_BUNDLE PlaneWidgetClipping.cpp )
 
target_link_libraries(ClippingPlaneWidget ${VTK_LIBRARIES})
