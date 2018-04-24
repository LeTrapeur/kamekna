# CMake project options
cmake_minimum_required (VERSION 3.0)
project (demo_2d_framework)

include_directories(${FRK2D_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE DEMO_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c)
set(EXECUTABLE_NAME "demo_FRK2D")
add_executable(${EXECUTABLE_NAME} ${DEMO_SOURCES})

target_link_libraries (${EXECUTABLE_NAME} ${FRK2D_LIBRARIES})

# Copy resource files into binary dir
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)


