/*
  this time to learn how to subscribe that speed value to our robot
 */
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"

using namespace std;
void chatterCallback(const std_msgs::String::ConstPtr& msg) {
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}
void chatterCallback_float(std_msgs::Float32 msg) {
  ROS_INFO("I heard: [%f]", msg.data);
}

void subscribe_cmd_vel(const geometry_msgs::Twist::ConstPtr &speed) {
  cout<<"get data cmd_vel linier x[%f], rotasi z[%f]"<<speed->linear.x<< speed->angular.z<<endl;
  // left = right = speed->linear.x * 10;
  // ==========================================================================
  // berikut ini adalah rumus differential driving yang aslinya untuk robot beroda 2, tapi bisa kita coba
  // tidak begitu bagus, tapi kita bisa mendapatkan gambaran nyata bagaimana mengendalikan robot sederhana
  // Lspeed = (2*V - W*d)/4*phi*r;
  // Rspeed = (2*V + W*d)/4*phi*r;
  // dimana V : kec. linear  = dari rqt linear.x
  //        W : kec. angular = dari rqt angular.x
  //        r : jarak roda ke pusat putar = 0.2 meter
  //        d : jarak antar roda = 10cm = 0.1 meter
  // kita mungkin perlu menambahkan skala kecepatan =speed_scale
  // ==========================================================================
  // Rspeed = (2*V + W*d)/4*phi*r;
  const float phi = 3.1415;
  float r = 0.2;
  float d = 0.1;
  float speed_scale = 100;
  // left   = (((2 * speed->linear.x) + (speed->angular.z * d))/4*phi*r) * speed_scale;
  // right  = (((2 * speed->linear.x) - (speed->angular.z * d))/4*phi*r) * speed_scale;
}



float x,y,z;
void subscribe_android_imu(const sensor_msgs::Imu::ConstPtr &imu){
  ROS_INFO("get data imu x=[%.2f], y=[%.2f], z=[%.2f]", imu->linear_acceleration.x, imu->linear_acceleration.y, imu->linear_acceleration.z);
  std::cout <<"okkk"  << "\n";
  x = imu->linear_acceleration.x;
  y = imu->linear_acceleration.y;
  z = imu->linear_acceleration.z;
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter_string", 1000, chatterCallback);
  ros::Subscriber sub_float = n.subscribe("speed", 1000, chatterCallback_float);
  ros::Subscriber sub_android_imu = n.subscribe<sensor_msgs::Imu>("/android/imu", 1, subscribe_android_imu);
  ros::Subscriber sub_rqt=n.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, subscribe_cmd_vel);
  
  ros::spin();

  return 0;
}
