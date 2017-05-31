cmake_minimum_required(VERSION 2.8.3)
project(wheel)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  tf
)
catkin_package()
include_directories(${catkin_INCLUDE_DIRS})
include_directories(include/wheel ${catkin_INCLUDE_DIRS})


add_executable(wheel_publisher src/wheel_publisher.cpp)
target_link_libraries(wheel_publisher ${catkin_LIBRARIES})

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})

# add_executable(tf_listener src/tf_listener.cpp)
# target_link_libraries(tf_listener ${catkin_LIBRARIES})

add_executable(rviz_control src/rviz_control.cpp)
target_link_libraries(rviz_control ${catkin_LIBRARIES})

add_executable(odometry_and_control_cpp src/odometry_and_control.cpp)
target_link_libraries(odometry_and_control_cpp ${catkin_LIBRARIES})


