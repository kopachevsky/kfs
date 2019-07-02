cmake_minimum_required(VERSION 2.8)

project(kfs)

# Useful CMake options for Qt projects
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Search desired Qt packages
find_package(Qt5Core REQUIRED)

# Create a list with all .cpp source files
set( project_sources
    kfs.cpp
    main.cpp
)

# Create executable with all necessary source files
add_executable(${PROJECT_NAME}
  ${project_sources}
)

qt5_use_modules( ${PROJECT_NAME} Core )
