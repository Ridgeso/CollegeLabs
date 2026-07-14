#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(Exec)

#----------------------------------------------------------------------------
add_definitions( ${Library_DEFINITIONS} )
include_directories(${Library_INCLUDE_DIR} )

#---------------------------------------------------------------------------
add_executable(vector main/vector.cpp)
target_link_libraries(vector Library)

#---------------------------------------------------------------------------
add_executable(complex main/complex.cpp)
target_link_libraries(complex Library)