cmake_minimum_required( VERSION 3.22 FATAL_ERROR )

project( overwatch CXX )

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD          20 )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

add_subdirectory( overwatch )
add_subdirectory( ut )
