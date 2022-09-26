# setting up cmake minimum version and project name
cmake_minimum_required(VERSION 3.8)
project(try_out_utils VERSION 0.1.0)

# setting c++ version standard to 17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(GNUInstallDirs)

# adding external packages required
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_cmake_catch2 REQUIRED)
find_package(Catch2 REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/point.cpp
)

target_include_directories(try_out_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(try_out_utils INTERFACE cxx_std_17)

include(CMakePackageConfigHelpers)

set(INSTALL_CONFIG_DIR "${CMAKE_INSTALL_LIBDIR}/try_out_utils/cmake")
set(PACKAGE_CONFIG_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/try_out_utils-config-version.cmake")
set(PACKAGE_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/try_out_utils-config.cmake")

configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/cmake/try_out_utils-config.cmake.in"
  ${PACKAGE_CONFIG_FILE}
  INSTALL_DESTINATION ${INSTALL_CONFIG_DIR}
)

write_basic_package_version_file(
  ${PACKAGE_CONFIG_VERSION_FILE}
  COMPATIBILITY ExactVersion
)

install(
  TARGETS try_out_utils
  EXPORT try_out_utils-targets
  DESTINATION lib
)

install(
    DIRECTORY include/try_out_utils
    DESTINATION include/
)

install(
  FILES
    ${PACKAGE_CONFIG_VERSION_FILE}
    ${PACKAGE_CONFIG_FILE}
  DESTINATION ${INSTALL_CONFIG_DIR}
)

install(
  EXPORT try_out_utils-targets
  FILE try_out_utils-targets.cmake
  NAMESPACE try_out_utils::
  DESTINATION ${INSTALL_CONFIG_DIR}
)

export(
  EXPORT try_out_utils-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/try_out_utils-targets.cmake
  NAMESPACE try_out_utils::
)

if(BUILD_TESTING)
  # listing all test files
  file(GLOB_RECURSE unit_test_srcs "test/*.cpp")

  # creating test target with listed test files
  ament_add_catch2(test_try_out_utils ${unit_test_srcs} TIMEOUT 300)

  # linking external and interal libraries required for target
  target_link_libraries(
    test_try_out_utils
    try_out_utils
    Catch2::Catch2
  )

  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

message("${CMAKE_INSTALL_PREFIX}")
message("${CMAKE_INSTALL_INCLUDEDIR}")
message("${CMAKE_INSTALL_BINDIR}")
message("${CMAKE_INSTALL_LIBDIR}")
message("${try_out_utils_CMAKE_DIR}")

ament_export_libraries(${PROJECT_NAME})
ament_export_include_directories("include")
ament_package()
