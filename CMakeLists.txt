cmake_minimum_required(VERSION 3.10.2)
project(kfs)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall --pedantic -g")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModule" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)



find_package(FUSE REQUIRED )
find_package(Log4cxx)

include_directories(${FUSE_INCLUDE_DIR})
include_directories(${Log4cxx_INCLUDE_DIR})

add_executable(kfs main.cpp main.h)
add_executable(kfs_demo demo-test.cpp)

target_link_libraries(kfs ${FUSE_LIBRARIES})
target_link_libraries(kfs ${Log4cxx_LIBRARY})

set_target_properties(kfs
    PROPERTIES 
    COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64")
