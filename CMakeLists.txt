# CMake project options
cmake_minimum_required (VERSION 3.0)
project (FRK2D_PROJECT)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#

# Needed for autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#

# Compiler options
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#

# Add project subdirectories
add_subdirectory(FRK2D)
set(FRK2D_LIBRARIES FRK2D)
add_subdirectory(demo)
#