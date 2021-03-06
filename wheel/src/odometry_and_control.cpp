#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

#include "wheel.h"
geometry_msgs::TransformStamped set_trans(geometry_msgs::TransformStamped odo, string header, string child, double _x, double _y, double _z, geometry_msgs::Quaternion _rot){
    
    cout<<"........."<<header<<endl;
    odo.header.stamp = current_time;
    odo.header.frame_id =header;
    odo.child_frame_id = child;
    odo.transform.translation.x = _x;
    odo.transform.translation.y = _y;
    odo.transform.translation.z = _z;
    odo.transform.rotation = _rot;  
    return odo;
}
nav_msgs::Odometry set_odo(nav_msgs::Odometry odom, string header, string child, double _x, double _y, double _z, geometry_msgs::Quaternion odom_quat, double dx, double dy, double dth, double _dt){
    odom.header.stamp = current_time;
    odom.header.frame_id = header;
    //set the position
    odom.pose.pose.position.x = _x;
    odom.pose.pose.position.y = _y;
    odom.pose.pose.position.z = _z;
    odom.pose.pose.orientation = odom_quat;
    //set the velocity
    odom.child_frame_id = child;
    odom.twist.twist.linear.x=dx/_dt;
    odom.twist.twist.linear.y=dy/_dt;
    odom.twist.twist.angular.z = dth/_dt;  
    return odom;
}
int main(int argc, char** argv){
  ros::init(argc, argv, "wheel_publisher");
  ros::NodeHandle n;
  ros::Rate r(20);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50); 
  // ros::Subscriber odom_sub = n.subscribe<nav_msgs::Odometry>("/odom", 1, subscribe_odom); 
  // ros::Subscriber sub_rqt=n.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, subscribe_cmd_vel);
  // ros::Subscriber sub_odo_from_cmd_vel=n.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, subscribe_odom);
  // ros::Subscriber sub_odo_from_imu=n.subscribe<geometry_msgs::Twist>("/read_imu", 1, subscribe_odom);
  ros::Subscriber sub_odo_from_cmd_vel=n.subscribe<geometry_msgs::Twist>("/read_odom", 1, subscribe_odom);
  
  tf::TransformBroadcaster odom_broadcaster;
  while(n.ok()){
    geometry_msgs::TransformStamped odom_trans;
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
    odom_trans = set_trans(odom_trans, "odom", "base", x, y, 0, odom_quat);
    odom_broadcaster.sendTransform(odom_trans);    
    odom_trans = set_trans(odom_trans, "odom", "laser", x, y, 0, odom_quat);
    odom_broadcaster.sendTransform(odom_trans);    
    odom_trans = set_trans(odom_trans, "odom", "left_back_wheel", x, y, 0, odom_quat);
    odom_broadcaster.sendTransform(odom_trans);    
    odom_trans = set_trans(odom_trans, "odom", "right_back_wheel", x, y, 0, odom_quat);
    odom_broadcaster.sendTransform(odom_trans);    
    /*
    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom = set_odo(odom,"odom","base", x, y, 0, odom_quat, delta_x, delta_y, delta_th, dt);
    //publish the message
    odom_pub.publish(odom);
    */
    last_time = current_time;
    ros::spinOnce();
    r.sleep();   
    
  }
}
