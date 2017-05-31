#ifndef __wheel_h__
#define __wheel_h__

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

using namespace std;
double th, ticks, angle;
const double degree = M_PI/180;
float lwheel, rwheel;

double x; 
double y;
// double th;
double v_left;//left motor speed
double v_right;//right motor speed
double vth;//angular velocity of robot
double deltaLeft;//no of ticks in left encoder since last update
double deltaRight;//no of ticks in right encoder since last update
double dt;
double delta_distance;//distance moved by robot since last update
double delta_th;//corresponging change in heading
double delta_x ;//corresponding change in x direction
double delta_y;//corresponding change in y direction
#define PI 3.14159265
#define TwoPI 6.28318531

ros::Time current_time, last_time;
long _PreviousLeftEncoderCounts = 0;
long _PreviousRightEncoderCounts = 0;
double DistancePerCount = (3.14159265 * 0.1)/650; //the wheel diameter is 0.1m
geometry_msgs::Twist act_pos;

void subscribe_cmd_vel(const geometry_msgs::Twist::ConstPtr &speed) {
}
void subscribe_odom_from_imu(const geometry_msgs::Twist::ConstPtr &speed) {
  act_pos.linear.x += speed->linear.x;
  act_pos.linear.y += speed->linear.y;
}
void subscribe_odom_from_cmd_vel(const geometry_msgs::Twist::ConstPtr &speed) {
  act_pos.linear.x += speed->linear.x;
  act_pos.linear.y += speed->linear.y;
}
// void subscribe_odom(const geometry_msgs::Vector3 msg){
void subscribe_odom(const geometry_msgs::Twist::ConstPtr &speed){
  const float phi = 3.1415;
  float r = 0.2;
  float d = 0.1;
  float speed_scale = 1;
  // lwheel   = (((2 * speed->linear.x) + (speed->angular.z * d))/4*phi*r) * speed_scale;
  // rwheel  = (((2 * speed->linear.x) - (speed->angular.z * d))/4*phi*r) * speed_scale;
  
  // ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  current_time = ros::Time::now();
  // deltaLeft  = msg->twist.twist.angular.x - _PreviousLeftEncoderCounts;
  // deltaRight = msg->twist.twist.angular.y - _PreviousRightEncoderCounts;
  deltaLeft  = speed->linear.x - _PreviousLeftEncoderCounts;
  deltaRight = speed->linear.y - _PreviousRightEncoderCounts;
  
  dt = (current_time - last_time).toSec();
  v_left = (deltaLeft * DistancePerCount)/dt;
  v_right = (deltaRight * DistancePerCount)/dt;
  delta_distance = 0.5f * (double) (deltaLeft+deltaRight) * DistancePerCount;
  delta_th = (double)(deltaRight-deltaLeft)*DistancePerCount/0.36f; //Distance between the two wheels is 0.36m
  delta_x = delta_distance*(double)cos(th);
  delta_y = delta_distance*(double)sin(th);
  x += delta_x;
  y += delta_y;
  th += delta_th;
  if (th > PI)
    th -= TwoPI;
  else
    if ( th <= -PI)
      th += TwoPI;

  // _PreviousLeftEncoderCounts = msg->twist.twist.angular.x;
  // _PreviousRightEncoderCounts = msg->twist.twist.angular.y;
  _PreviousLeftEncoderCounts = speed->linear.x;
  _PreviousRightEncoderCounts = speed->linear.y;
  last_time = current_time;

  cout<<"============================================================="<<endl;
  cout<< "x:["<< x <<"],y:["<< y <<"]"<<endl;
  cout<<"dt:["<< dt <<"]"<<endl;
  cout<<"v left:["<< v_left <<"]"<<endl;
  cout<<"v right:["<< v_right <<"]"<<endl;
  cout<<"delta distance:["<< delta_distance <<"]"<<endl;
  cout <<"============================================================="<<endl;
}


#endif
