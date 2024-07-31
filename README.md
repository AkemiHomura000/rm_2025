Sentry_2025
===

Abstract:决策+导航
前有垃圾，所以接下来跑路会很有用

## Install & Dependence

- ubuntu 22.04
- ros2 humble
- qt6 (for node_editor and sim_referee,在CMakeLists里修改qt6路径)
- spdlog
- fmt

## Use

- for match

  ```
  
  ```

- for test

  ```
  
  ```

## Directory Hierarchy
```
|—— node_editor
|    |—— CMakeLists.txt
|    |—— config
|        |—— graph.json
|        |—— tree.yaml
|    |—— inc
|        |—— FlowChartScene.h
|        |—— FlowChartView.h
|        |—— Node_Serializable.h
|        |—— mainwindow.h
|        |—— node_content_widget.h
|        |—— node_edge.h
|        |—— node_graphics_cutLine.h
|        |—— node_graphics_edge.h
|        |—— node_graphics_node.h
|        |—— node_graphics_socket.h
|        |—— node_node.h
|        |—— node_scene.h
|        |—— node_socket.h
|    |—— main.cpp
|    |—— mainwindow.cpp
|    |—— mainwindow.h
|    |—— mainwindow.ui
|    |—— package.xml
|    |—— src
|        |—— FlowChartScene.cpp
|        |—— FlowChartView.cpp
|        |—— Node_Serializable.cpp
|        |—— mainwindow.cpp
|        |—— node_content_widget.cpp
|        |—— node_edge.cpp
|        |—— node_graphics_cutLine.cpp
|        |—— node_graphics_edge.cpp
|        |—— node_graphics_node.cpp
|        |—— node_graphics_socket.cpp
|        |—— node_node.cpp
|        |—— node_scene.cpp
|        |—— node_socket.cpp
|    |—— thirdpkg
|        |—— rapidjson
|            |—— allocators.h
|            |—— cursorstreamwrapper.h
|            |—— document.h
|            |—— encodedstream.h
|            |—— encodings.h
|            |—— error
|                |—— en.h
|                |—— error.h
|            |—— filereadstream.h
|            |—— filewritestream.h
|            |—— fwd.h
|            |—— internal
|                |—— biginteger.h
|                |—— clzll.h
|                |—— diyfp.h
|                |—— dtoa.h
|                |—— ieee754.h
|                |—— itoa.h
|                |—— meta.h
|                |—— pow10.h
|                |—— regex.h
|                |—— stack.h
|                |—— strfunc.h
|                |—— strtod.h
|                |—— swap.h
|            |—— istreamwrapper.h
|            |—— memorybuffer.h
|            |—— memorystream.h
|            |—— msinttypes
|                |—— inttypes.h
|                |—— stdint.h
|            |—— ostreamwrapper.h
|            |—— pointer.h
|            |—— prettywriter.h
|            |—— rapidjson.h
|            |—— reader.h
|            |—— schema.h
|            |—— stream.h
|            |—— stringbuffer.h
|            |—— uri.h
|            |—— writer.h
|        |—— spdlog
|            |—— async.h
|            |—— async_logger-inl.h
|            |—— async_logger.h
|            |—— cfg
|                |—— argv.h
|                |—— env.h
|                |—— helpers-inl.h
|                |—— helpers.h
|            |—— common-inl.h
|            |—— common.h
|            |—— details
|                |—— backtracer-inl.h
|                |—— backtracer.h
|                |—— circular_q.h
|                |—— console_globals.h
|                |—— file_helper-inl.h
|                |—— file_helper.h
|                |—— fmt_helper.h
|                |—— log_msg-inl.h
|                |—— log_msg.h
|                |—— log_msg_buffer-inl.h
|                |—— log_msg_buffer.h
|                |—— mpmc_blocking_q.h
|                |—— null_mutex.h
|                |—— os-inl.h
|                |—— os.h
|                |—— periodic_worker-inl.h
|                |—— periodic_worker.h
|                |—— registry-inl.h
|                |—— registry.h
|                |—— synchronous_factory.h
|                |—— tcp_client-windows.h
|                |—— tcp_client.h
|                |—— thread_pool-inl.h
|                |—— thread_pool.h
|                |—— windows_include.h
|            |—— fmt
|                |—— bin_to_hex.h
|                |—— bundled
|                    |—— LICENSE.rst
|                    |—— chrono.h
|                    |—— color.h
|                    |—— compile.h
|                    |—— core.h
|                    |—— format-inl.h
|                    |—— format.h
|                    |—— locale.h
|                    |—— os.h
|                    |—— ostream.h
|                    |—— posix.h
|                    |—— printf.h
|                    |—— ranges.h
|                |—— chrono.h
|                |—— fmt.h
|                |—— ostr.h
|            |—— formatter.h
|            |—— fwd.h
|            |—— logger-inl.h
|            |—— logger.h
|            |—— pattern_formatter-inl.h
|            |—— pattern_formatter.h
|            |—— sinks
|                |—— android_sink.h
|                |—— ansicolor_sink-inl.h
|                |—— ansicolor_sink.h
|                |—— base_sink-inl.h
|                |—— base_sink.h
|                |—— basic_file_sink-inl.h
|                |—— basic_file_sink.h
|                |—— daily_file_sink.h
|                |—— dist_sink.h
|                |—— dup_filter_sink.h
|                |—— hourly_file_sink.h
|                |—— msvc_sink.h
|                |—— null_sink.h
|                |—— ostream_sink.h
|                |—— ringbuffer_sink.h
|                |—— rotating_file_sink-inl.h
|                |—— rotating_file_sink.h
|                |—— sink-inl.h
|                |—— sink.h
|                |—— stdout_color_sinks-inl.h
|                |—— stdout_color_sinks.h
|                |—— stdout_sinks-inl.h
|                |—— stdout_sinks.h
|                |—— syslog_sink.h
|                |—— systemd_sink.h
|                |—— tcp_sink.h
|                |—— win_eventlog_sink.h
|                |—— wincolor_sink-inl.h
|                |—— wincolor_sink.h
|            |—— spdlog-inl.h
|            |—— spdlog.h
|            |—— stopwatch.h
|            |—— tweakme.h
|            |—— version.h
|—— robot_action
|    |—— CMakeLists.txt
|    |—— action
|        |—— CommonAction.action
|        |—— ExampleAction.action
|    |—— package.xml
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
|    |—— config
|        |—— test.yaml
|    |—— include
|        |—— node
|            |—— action_node.hpp
|            |—— behavior_tree.hpp
|            |—— condition_node.hpp
|            |—— observe_node.hpp
|        |—— perception
|            |—— blackboard.hpp
|        |—— tools
|            |—— logger.hpp
|            |—— logger_test.cpp
|    |—— package.xml
|    |—— src
|        |—— node
|            |—— action_node.cpp
|            |—— behavior_tree.cpp
|            |—— condition_node.cpp
|            |—— observe_node.cpp
|        |—— perception
|            |—— blackboard.cpp
|    |—— test
|        |—— action_test.cpp
|        |—— condition_test.cpp
|        |—— head_test.cpp
|        |—— sim_action_server.cpp
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
