# Create a test library with common test utils
add_library(test_utils OBJECT 
  test_utils.cpp
  mock_serial_port.cpp
)
target_include_directories(test_utils 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(test_utils 
  PUBLIC 
    Catch2::Catch2 
    Boost::system
)

# Compile test_main separately to speed up builds
add_library(test_main OBJECT test_main.cpp)
target_link_libraries(test_main PUBLIC Catch2::Catch2WithMain)

# Add servo reader test
add_executable(test_st3215_servo_reader 
  test_st3215_servo_reader.cpp 
  ${CMAKE_SOURCE_DIR}/src/perseus-arm-teleop.cpp
  $<TARGET_OBJECTS:test_main>
  $<TARGET_OBJECTS:test_utils>
)
target_include_directories(test_st3215_servo_reader
  PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(test_st3215_servo_reader 
  PRIVATE 
    Catch2::Catch2WithMain 
    Boost::system
    yaml-cpp
    pthread
)

# Add position scaling test
add_executable(test_position_scaling
  test_position_scaling.cpp
  $<TARGET_OBJECTS:test_main>
)
target_include_directories(test_position_scaling
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(test_position_scaling
  PRIVATE
    Catch2::Catch2WithMain
)

# Register tests with CTest
include(Catch)
catch_discover_tests(test_st3215_servo_reader)
catch_discover_tests(test_position_scaling)