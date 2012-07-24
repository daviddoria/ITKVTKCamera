cmake_minimum_required(VERSION 2.6)

PROJECT(ITKVTKCamera)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_library(ITKVTKCamera ITKVTKCamera.cpp)
target_link_libraries(ITKVTKCamera ${VTK_LIBRARIES})

add_subdirectory(Examples)