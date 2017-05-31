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

void subscribe_cmd_vel(const geometry_msgs::Twist::ConstPtr &speed) {
}
// double x;
void subscribe_odom(const nav_msgs::Odometry::ConstPtr& msg){
  const float phi = 3.1415;
  float r = 0.2;
  float d = 0.1;
  float speed_scale = 1;
  // lwheel   = (((2 * speed->linear.x) + (speed->angular.z * d))/4*phi*r) * speed_scale;
  // rwheel  = (((2 * speed->linear.x) - (speed->angular.z * d))/4*phi*r) * speed_scale;
  
  // ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  current_time = ros::Time::now();
  deltaLeft  = msg->twist.twist.angular.x - _PreviousLeftEncoderCounts;
  deltaRight = msg->twist.twist.angular.y - _PreviousRightEncoderCounts;
  // cout << "delta_left[" << deltaLeft << "]\n";
  
  dt = (current_time - last_time).toSec();
  v_left = deltaLeft * DistancePerCount/dt;
  v_right = deltaRight * DistancePerCount/dt;
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

  _PreviousLeftEncoderCounts = msg->twist.twist.angular.x;
  _PreviousRightEncoderCounts = msg->twist.twist.angular.y;
  last_time = current_time;

  cout <<"============================================================="<<endl;
  cout<<"dt:["<< dt <<"]"<<endl;

  cout<<"v left:["<< v_left <<"]"<<endl;
  cout<<"v right:["<< v_right <<"]"<<endl;
  cout<<"delta distance:["<< delta_distance <<"]"<<endl;
  cout <<"============================================================="<<endl;
}
int main(int argc, char** argv){
  ros::init(argc, argv, "wheel_publisher");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50); 
  ros::Subscriber odom_sub = n.subscribe<nav_msgs::Odometry>("/odom", 1, subscribe_odom); 
  tf::TransformBroadcaster odom_broadcaster;

  ros::Subscriber sub_rqt=n.subscribe<geometry_msgs::Twist>\
      ("/cmd_vel", 1, subscribe_cmd_vel);
   
  while(n.ok()){
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
    // pertama kita publish transformasi menggunakan  tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0;
    odom_trans.transform.rotation = odom_quat;

    // kirim transformasi
    odom_broadcaster.sendTransform(odom_trans);
     //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "base";
    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;
    //set the velocity
    odom.child_frame_id = "left_back_wheel";
    odom.twist.twist.linear.x=delta_x/dt;
    odom.twist.twist.linear.y=delta_y/dt;
    odom.twist.twist.angular.z = delta_th/dt;
    //publish the message
    odom_pub.publish(odom);
    last_time = current_time;

    r.sleep();
    ros::spinOnce();
  }
}
