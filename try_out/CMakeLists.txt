cmake_minimum_required(VERSION 3.8)
project(try_out)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(try_out_utils REQUIRED)
find_package(ament_cmake_catch2 REQUIRED)
find_package(Catch2 REQUIRED)

include_directories(include)

add_library(try_out SHARED
  src/point_checker.cpp
)

target_include_directories(try_out PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  ${try_out_utils_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS})

add_executable(
  try src/point_checker.cpp)

target_include_directories(try PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_target_dependencies(
  try
  rclcpp
  try_out_utils)

install(TARGETS
try
DESTINATION lib/${PROJECT_NAME})

install(
  TARGETS
  try_out
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
    DIRECTORY include/
    DESTINATION include/
)

if(BUILD_TESTING)
  file(GLOB_RECURSE unit_test_srcs "test/*.cpp")

  ament_add_catch2(test_try_out ${unit_test_srcs} TIMEOUT 300)

  target_include_directories(test_try_out
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>)

  target_link_libraries(test_try_out
  try_out
  try_out_utils::try_out_utils
  Catch2::Catch2
  ${rclcpp_LIBRARIES})

  find_package(ament_lint_auto REQUIRED)
  find_package(try_out_utils REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
