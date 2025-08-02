cmake_minimum_required(VERSION 3.0.2)
project(tfluna_ros)

find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs)
find_package(Boost REQUIRED COMPONENTS system)

catkin_package(INCLUDE_DIRS include)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(tfluna_ros_node src/tfluna_ros_node.cpp src/tfluna.cpp)

target_link_libraries(tfluna_ros_node ${catkin_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++11")

install(
  TARGETS tfluna_ros_node tfluna_ros_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
  DIRECTORY include
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING
  PATTERN "*.h"
)

install(
  FILES launch/tfluna.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
