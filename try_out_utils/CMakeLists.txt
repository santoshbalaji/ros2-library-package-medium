cmake_minimum_required(VERSION 3.8)
project(try_out_utils)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Adding external packages required
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_cmake_catch2 REQUIRED)
find_package(Catch2 REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/point.cpp
)

add_library(try_out_utils::try_out_utils ALIAS try_out_utils)

target_include_directories(try_out_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION lib
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION bin
# )

install(
  TARGETS try_out_utils
  EXPORT  try_out_utils-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(
  EXPORT try_out_utils-targets
  FILE try_out_utils-targets.cmake
  NAMESPACE try_out_utils::
  DESTINATION lib
)

install(
  DIRECTORY include/
  DESTINATION include/
)

if(BUILD_TESTING)
  file(GLOB_RECURSE unit_test_srcs "test/*.cpp")

  ament_add_catch2(test_try_out_utils ${unit_test_srcs} TIMEOUT 300)

  target_link_libraries(
    test_try_out_utils
    try_out_utils
    Catch2::Catch2
  )

  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_libraries(${PROJECT_NAME})
ament_export_include_directories("include")
ament_package()
