cmake_minimum_required(VERSION 3.10.2)
project(kfs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModule" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)



find_package(FUSE REQUIRED)

include_directories(${FUSE_INCLUDE_DIR})

add_executable(kfs main.cpp main.h)
target_link_libraries(kfs ${FUSE_LIBRARIES})

set_target_properties(kfs 
    PROPERTIES 
    COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64")