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



find_package(FUSE REQUIRED)

include_directories(${FUSE_INCLUDE_DIR})

add_executable(kfs main.cpp main.h)
target_link_libraries(kfs ${FUSE_LIBRARIES})

if(SPDLOG_BUILD_EXAMPLE_HO)
    add_executable(example_header_only example.cpp)
    spdlog_enable_warnings(example_header_only)
    target_link_libraries(example_header_only PRIVATE spdlog::spdlog_header_only)
endif()

# Create logs directory
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")

set_target_properties(kfs 
    PROPERTIES 
    COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64")