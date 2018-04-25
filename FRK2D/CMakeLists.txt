# CMake project options
cmake_minimum_required (VERSION 3.0)
project (FRK2D VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE FRAMEWORK_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/source/external/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/external/*.c)

add_library(FRK2D SHARED ${FRAMEWORK_SOURCES})

set_target_properties(FRK2D PROPERTIES VERSION ${PROJECT_VERSION})

# Make sure the compiler can find include files for our library
# when other libraries or executables link to it
target_include_directories (FRK2D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# SFML setup 
find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(FRK2D ${SFML_LIBRARIES})
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
target_link_libraries(FRK2D ${BOX2D_LIBRARIES})
#

#TGUI setup
set(TGUI_LIBRARIES tgui)
target_link_libraries(FRK2D ${TGUI_LIBRARIES})
#

# TMX setup
set(TMX_LIBRARIES tmx-loader)
target_link_libraries(FRK2D ${TMX_LIBRARIES})
#