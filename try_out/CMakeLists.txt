# setting up cmake minimum version and project name
cmake_minimum_required(VERSION 3.8)
project(try_out VERSION 0.1.0)

# setting c++ version standard to 17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# adding compiler arguments
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# adding external dependencies required
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(try_out_utils REQUIRED)
find_package(ament_cmake_catch2 REQUIRED)
find_package(Catch2 REQUIRED)

# creating library package with reference to required files
add_library(try_out SHARED
  src/point_checker.cpp
)

# including external directory reference for the created library
target_include_directories(try_out PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  ${rclcpp_INCLUDE_DIRS})

# including external library reference for the created library
target_link_libraries(try_out
  PUBLIC
    try_out_utils::try_out_utils
)

# creating executables with reference to required files
add_executable(
  try src/point_checker.cpp)

# including external directory reference for the created executable
target_include_directories(try PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  ${rclcpp_INCLUDE_DIRS})

# including external library reference for the created executable
target_link_libraries(try
  ${rclcpp_LIBRARIES}
  try_out_utils::try_out_utils
)

# installing executable file
install(TARGETS
try
DESTINATION lib})

# installing library file
install(
  TARGETS try_out
  DESTINATION lib
)

# installing all reference header files
install(
    DIRECTORY include/try_out
    DESTINATION include/
)

# checking whether build includes test
if(BUILD_TESTING)
  # listing files for testing
  file(GLOB_RECURSE unit_test_srcs "test/*.cpp")

  # adding listed files for testing
  ament_add_catch2(test_try_out ${unit_test_srcs} TIMEOUT 300)

  # linking libraries required to the current package for testing
  target_link_libraries(test_try_out
  try_out
  try_out_utils::try_out_utils
  Catch2::Catch2)

  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
