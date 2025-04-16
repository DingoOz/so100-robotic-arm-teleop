# PROJECT SETUP
cmake_minimum_required(VERSION 3.10)

project(
  arm-teleop-direct
  VERSION 1.0.0
  LANGUAGES CXX)

# Add testing support to the project
enable_testing()

# Option to build tests
option(BUILD_TESTS "Build test suite" OFF)

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

# Find required packages
find_package(Boost REQUIRED COMPONENTS system)
find_package(Curses REQUIRED)
find_package(yaml-cpp REQUIRED)

# Optional stack trace support (not ROS dependent)
option(ENABLE_BACKWARD "Enable backward-cpp (stack traces)" OFF)
if(ENABLE_BACKWARD)
  # Try to find the backward-cpp package
  find_package(Backward QUIET)
  if(Backward_FOUND)
    add_definitions(-DHAS_BACKWARD)
    # Backward will handle adding necessary dependencies
  else()
    message(STATUS "Backward-cpp not found. Stack traces will be disabled.")
  endif()
endif()

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

# If backward was found, link it
if(TARGET Backward::Backward)
  target_link_libraries(${PROJECT_NAME} PRIVATE Backward::Backward)
endif()

# INSTALL (Executables)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
# Versioning
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# Test configuration (only if BUILD_TESTS is ON)
if(BUILD_TESTS)
  # Add Catch2 (via FetchContent)
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0 # Use the latest release
  )
  FetchContent_MakeAvailable(Catch2)
  
  # Create test directory
  add_subdirectory(tests)
endif()