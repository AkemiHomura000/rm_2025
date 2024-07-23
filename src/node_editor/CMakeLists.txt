cmake_minimum_required(VERSION 3.8)
project(node_editor)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/lp1/Qt/6.7.2/gcc_64/lib/cmake") # 设置Qt的路径

# find_package(QT NAMES Qt6  REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
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

include_directories(inc)
include_directories(thirdpkg)
FILE(GLOB_RECURSE SOURCE_FILES inc/*.h src/*.cpp)

add_executable(node_editor
  main.cpp

  ${SOURCE_FILES}
)
ament_target_dependencies(node_editor
  "rclcpp"
)

target_link_libraries(node_editor Qt6::Widgets)
install(TARGETS node_editor
  DESTINATION lib/${PROJECT_NAME})

ament_package()
