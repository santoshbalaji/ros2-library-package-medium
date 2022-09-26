# setting up cmake minimum version and project name
cmake_minimum_required(VERSION 3.8)
project(try_out_utils VERSION 0.1.0)

# setting c++ version standard to 17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# adding compiler arguments
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# added to use install directory variables
include(GNUInstallDirs)

# adding external dependencies required
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_cmake_catch2 REQUIRED)
find_package(Catch2 REQUIRED)

# creating library package with reference to required files
add_library(${PROJECT_NAME} SHARED
  src/point.cpp
)

# including external directories reference for the created library
target_include_directories(try_out_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# helpers functions for creating config files that can be included by other projects to find and use a package
include(CMakePackageConfigHelpers)

set(INSTALL_CONFIG_DIR "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake")
set(PACKAGE_CONFIG_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(PACKAGE_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")

# creating version configuration for external package to perform compatibility check
configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
  ${PACKAGE_CONFIG_FILE}
  INSTALL_DESTINATION ${INSTALL_CONFIG_DIR}
)

# creating version configuration for external package to perform compatibility check
write_basic_package_version_file(
  ${PACKAGE_CONFIG_VERSION_FILE}
  COMPATIBILITY ExactVersion
)

# installing library files
install(
  TARGETS try_out_utils
  EXPORT try_out_utils-targets
  DESTINATION lib
)

# installing all reference header files
install(
    DIRECTORY include/try_out_utils
    DESTINATION include/
)

# installing cmake config files for try_out_utils
install(
  FILES
    ${PACKAGE_CONFIG_VERSION_FILE}
    ${PACKAGE_CONFIG_FILE}
  DESTINATION ${INSTALL_CONFIG_DIR}
)

# installing cmake config files for try_out_utils-targets
install(
  EXPORT try_out_utils-targets
  FILE try_out_utils-targets.cmake
  NAMESPACE try_out_utils::
  DESTINATION ${INSTALL_CONFIG_DIR}
)

# exporting the try_out_utils-target cmake config to build folder
export(
  EXPORT try_out_utils-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/try_out_utils-targets.cmake
  NAMESPACE try_out_utils::
)

# checking whether build includes test
if(BUILD_TESTING)
  # listing files for testing
  file(GLOB_RECURSE unit_test_srcs "test/*.cpp")

  # adding listed files for testing
  ament_add_catch2(test_try_out_utils ${unit_test_srcs} TIMEOUT 300)

  # linking libraries required to the current package for testing
  target_link_libraries(
    test_try_out_utils
    try_out_utils
    Catch2::Catch2
  )

  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
