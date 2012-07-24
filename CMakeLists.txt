cmake_minimum_required(VERSION 2.6)

PROJECT(ITKVTKCamera)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

FIND_PACKAGE(ITK REQUIRED ITKCommon ITKIOImageBase ITKIOPNG ITKIOMeta
ITKImageIntensity ITKImageFeature ITKMathematicalMorphology ITKBinaryMathematicalMorphology ITKDistanceMap)
INCLUDE(${ITK_USE_FILE})

if(NOT TARGET ITKVTKHelpers)
  add_subdirectory(ITKVTKHelpers)
  include_directories(${ITKVTKHelpers_includes})
endif()

add_library(ITKVTKCamera ITKVTKCamera.cpp)
target_link_libraries(ITKVTKCamera ${VTK_LIBRARIES} ${ITK_LIBRARIES})

# Allow inheritance of include directories
if(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  set(ITKVTKCamera_includes ${ITKVTKHelpers_includes} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
endif()

SET(ITKVTKCamera_BuildExamples OFF CACHE BOOL "ITKVTKCamera_BuildExamples")
if(ITKVTKCamera_BuildExamples)
  add_subdirectory(Examples)
endif(ITKVTKCamera_BuildExamples)
