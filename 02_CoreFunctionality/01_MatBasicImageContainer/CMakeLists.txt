cmake_minimum_required (VERSION 2.6)
project (01_MatBasicImageContainer)
find_package (OpenCV REQUIRED)
include_directories (${OpenCV_INCLUDE_DIRS})
add_executable (01_MatBasicImageContainer 01_MatBasicImageContainer.cpp)
target_link_libraries (01_MatBasicImageContainer ${OpenCV_LIBS})
