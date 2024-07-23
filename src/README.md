Title
===
Abstract:xxx

## Install & Dependence
- ubuntu 22.04
- ros2 humble
- qt6 (for node_editor and sim_referee,在CMakeLists里修改qt6路径)
- spdlog
- fmt 

## Use
- for train
  ```
  
  ```
- for test
  ```
  
  ```

## Directory Hierarchy
```
|—— README.md
|—— robot_msg
|    |—— CMakeLists.txt
|    |—— msg
|        |—— MyMsg.msg
|        |—— RefereeInfoMsg.msg
|        |—— RobotHpMsg.msg
|    |—— package.xml
|—— sim_referee
|    |—— CMakeLists.txt
|    |—— include
|        |—— sim_referee
|        |—— sim_referee.h
|    |—— package.xml
|    |—— src
|        |—— main.cpp
|        |—— sim_referee.cpp
|        |—— sim_referee.ui
|—— sp_decision
|    |—— CMakeLists.txt
|    |—— include
|        |—— node
|            |—— node.hpp
|        |—— tools
|            |—— logger.hpp
|            |—— logger_test.cpp
|    |—— package.xml
|    |—— src
|        |—— node
|            |—— node.cpp
|            |—— node_test.cpp
```
## Code Details
### Tested Platform
- software
  ```
  
  ```
- hardware
  ```
  
  ```
### Hyper parameters
```
```

  

