cmake_minimum_required(VERSION 3.8)
project(sp_decision)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

find_package(rclcpp_action REQUIRED)
find_package(robot_action REQUIRED)
find_package(action_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)
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

# -----------------logger_test-----------------
add_executable(logger_test
  include/tools/logger_test.cpp
)
ament_target_dependencies(logger_test
  fmt)
target_link_libraries(logger_test fmt::fmt)
install(TARGETS logger_test
  DESTINATION lib/${PROJECT_NAME})

# -----------------logger_test-----------------

# -----------------node_test-----------------

add_executable(condition_node_test
  test/condition_test.cpp
  src/node/condition_node.cpp
  src/perception/blackboard.cpp
)
ament_target_dependencies(condition_node_test
  fmt
  rclcpp
  std_msgs
  rclcpp_action
  robot_action
  action_msgs)
target_link_libraries(condition_node_test fmt::fmt)
install(TARGETS condition_node_test
  DESTINATION lib/${PROJECT_NAME})

add_executable(head_node_test
  test/head_test.cpp
  src/node/behavior_tree.cpp
  src/node/observe_node.cpp
  src/node/action_node.cpp
  src/node/condition_node.cpp
  src/perception/blackboard.cpp
)
ament_target_dependencies(head_node_test
  fmt
  rclcpp
  std_msgs
  rclcpp_action
  robot_action
  action_msgs
  ament_index_cpp)
target_link_libraries(head_node_test fmt::fmt yaml-cpp)
install(TARGETS head_node_test
  DESTINATION lib/${PROJECT_NAME})

# -----------------node_test-----------------

# -----------------action_test-----------------
add_executable(sim_action_serever
  test/sim_action_server.cpp
)
ament_target_dependencies(sim_action_serever
  rclcpp
  std_msgs
  rclcpp_action
  robot_action
  action_msgs)
target_link_libraries(sim_action_serever fmt::fmt)
install(TARGETS sim_action_serever
  DESTINATION lib/${PROJECT_NAME})

add_executable(test_action_client
  src/node/action_node.cpp
  src/node/observe_node.cpp
  test/action_test.cpp
)
ament_target_dependencies(test_action_client
  rclcpp
  std_msgs
  rclcpp_action
  robot_action
  action_msgs)
target_link_libraries(test_action_client fmt::fmt)
install(TARGETS test_action_client
  DESTINATION lib/${PROJECT_NAME})

# -----------------action_test-----------------
ament_package()
