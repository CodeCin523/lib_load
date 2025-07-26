cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(lib_load VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/default)
add_subdirectory(src/encrypt)
add_subdirectory(src/multiApp)
add_subdirectory(src/sharedFunc)