#!/bin/bash
# Script to provide a fallback CMakeLists.txt for CI environments where ROS is not available

set -e

# Check if this is being run in a CI environment
if [ -z "$CI" ]; then
  echo "This script is intended to be run in CI environments only."
  exit 1
fi

echo "Creating fallback CMakeLists.txt without ROS dependencies..."

cat > CMakeLists.txt << 'EOF'
# PROJECT SETUP
cmake_minimum_required(VERSION 3.10)

project(
  arm-teleop-direct
  VERSION 1.0.0
  LANGUAGES CXX)

# credit https://www.kitware.com/cmake-and-the-default-build-type/
set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(
    STATUS
      "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
      "${default_build_type}"
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()
# we always want debug info for stack tracing, so switch to RelWithDebInfo from
# Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
# Add -Werror flag for release builds
if(CMAKE_BUILD_TYPE MATCHES "Rel.*")
  add_compile_options(-Werror)
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# INCLUDE DEPENDENCIES

# Find other required packages
find_package(Boost REQUIRED COMPONENTS system)
find_package(Curses REQUIRED)
find_package(yaml-cpp REQUIRED)

# COMPILE (Executables)

# Find all source files in the src directory
file(GLOB_RECURSE CODE_SOURCES src/*.cpp)
# Add the target with those sources
add_executable(${PROJECT_NAME} ${CODE_SOURCES})
# Set the include directories
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Link private dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system ${CURSES_LIBRARIES}
                                              yaml-cpp pthread)

# INSTALL (Executables)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
# Versioning
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
EOF

echo "Fallback CMakeLists.txt created. Use this only if the standard build fails due to missing ROS dependencies."
echo "To use: cp CMakeLists.txt.ci CMakeLists.txt && mkdir -p build && cd build && cmake .. && make"