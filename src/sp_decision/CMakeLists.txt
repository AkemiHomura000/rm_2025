cmake_minimum_required(VERSION 3.8)
project(sp_decision)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(fmt REQUIRED)
find_package(rclcpp REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
include_directories(include)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)

  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

#-----------------logger_test-----------------
add_executable(logger_test
  include/tools/logger_test.cpp
)
ament_target_dependencies(logger_test
  fmt)
target_link_libraries(logger_test fmt::fmt)
install(TARGETS logger_test
  DESTINATION lib/${PROJECT_NAME})
#-----------------logger_test-----------------

#-----------------node_test-----------------
add_executable(node_test
  src/node/node_test.cpp
  src/node/node.cpp
)
ament_target_dependencies(node_test
  fmt)
target_link_libraries(node_test fmt::fmt)
install(TARGETS node_test
  DESTINATION lib/${PROJECT_NAME})
#-----------------node_test-----------------
ament_package()
