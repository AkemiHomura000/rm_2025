Title
===
Abstract:xxx

## Install & Dependence
- ubuntu 22.04
- ros2 humble
- qt5
- spdlog
- fmt 

## Use
- for train
  ```
  python train.py
  ```
- for test
  ```
  python test.py
  ```

## Directory Hierarchy
```
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
  OS: Debian unstable (May 2021), Ubuntu LTS
  Python: 3.8.5 (anaconda)
  PyTorch: 1.7.1, 1.8.1
  ```
- hardware
  ```
  CPU: Intel Xeon 6226R
  GPU: Nvidia RTX3090 (24GB)
  ```
### Hyper parameters
```
```

  

