cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
project (framework2d)

# needed for autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(Include)
file(GLOB_RECURSE SOURCES Source/*.cpp Source/*.c)
set(EXECUTABLE_NAME "framework2d")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# SFML setup 
find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
#

# Box2D setup
set ( BOX2D_FOUND 1 )
set ( BOX2D_USE_FILE     "/usr/lib/x86_64-linux-gnu/cmake/Box2D/UseBox2D.cmake" )

set ( BOX2D_DEFINITIONS  "" )
set ( BOX2D_INCLUDE_DIR  "/usr/include" )
set ( Box2D_INCLUDE_DIRS "/usr/include" ) # deprecated
set ( BOX2D_INCLUDE_DIRS "/usr/include" )
set ( BOX2D_LIBRARY      "Box2D" )
set ( BOX2D_LIBRARIES    "Box2D" )
set ( BOX2D_LIBRARY_DIRS "/usr/lib/x86_64-linux-gnu" )
set ( BOX2D_ROOT_DIR     "/usr" )

set ( BOX2D_VERSION_STRING "2.3.0" )

add_definitions     ( ${BOX2D_DEFINITIONS} )
include_directories ( ${BOX2D_INCLUDE_DIRS} )
link_directories    ( ${BOX2D_LIBRARY_DIRS} )
target_link_libraries(${EXECUTABLE_NAME} ${BOX2D_LIBRARIES})
#

#TGUI setup
target_link_libraries(${EXECUTABLE_NAME} tgui)
# 



