project(test)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
find_package(PCL 1.7 REQUIRED )
include_directories(${PCL_INCLUDE_DIRS} )
link_directories(${PCL_LIBRARY_DIRS} )
add_definitions(${PCL_DEFINITIONS}) 

add_executable (main main.cpp )
target_link_libraries(main ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_LIBRARIES} ${PCL_KDTREE_LIBRARY} ${PCL_SEARCH_LIBRARY} ${PCL_SURFACE_LIBRARY} ${PCL_FEATURES_LIBRARY} ) 


