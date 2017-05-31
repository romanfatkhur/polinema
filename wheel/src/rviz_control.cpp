#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

double x, y;
void subscribe_cmd_vel(const geometry_msgs::Twist::ConstPtr &speed) {
  x = speed->linear.x*40;
  y = speed->linear.z*40;
}
int main(int argc, char** argv){
  ros::init(argc, argv, "rviz_control");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50); 
  ros::Subscriber sub_rqt=n.subscribe<geometry_msgs::Twist>\
      ("/cmd_vel", 1, subscribe_cmd_vel);
  tf::TransformBroadcaster broadcaster;
  while(n.ok()){
    nav_msgs::Odometry odom;
    tf::StampedTransform current_frame;
    tf::Transform src_point;
    tf::Quaternion quat;
    tf::Vector3 translasi;

    //==========base========
    quat = tf::Quaternion(0, 0, 0, 1);
    translasi = tf::Vector3( x, y, 0);
    src_point = tf::Transform(quat, translasi);
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "base");
    broadcaster.sendTransform(current_frame);
    //==========end of base========

    //==========roda kanan========
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "left_back_wheel");
    broadcaster.sendTransform(current_frame);
    //==========end of roda kanan========

    //==========roda kiri========
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "right_back_wheel");
    broadcaster.sendTransform(current_frame);
    //==========end of roda kiri========
    r.sleep();
    ros::spinOnce();
  }
}
