# Allow headers in tests to be included like
# #include "ITKVTKCamera.h" rather than needing
# #include "ITKVTKCamera/ITKVTKCamera.h"
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(ExamplePNG ExamplePNG.cpp)
target_link_libraries(ExamplePNG ITKVTKCamera)

add_executable(ExampleMHA ExampleMHA.cpp)
target_link_libraries(ExampleMHA ITKVTKCamera)
