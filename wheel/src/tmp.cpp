nav_msgs::Odometry odom;
    tf::StampedTransform current_frame;
    tf::Transform src_point;
    tf::Quaternion quat;
    tf::Vector3 translasi;
    //==========base========
    quat = tf::Quaternion(0, 0, 0, 1);
    // translasi = tf::Vector3( delta_distance, 0, 0);
    translasi = tf::Vector3( x, y, 0);
    // translasi = tf::Vector3( (cos(angle)/4)*deltaLeft, (sin(angle)/4)*deltaLeft, 0);
    src_point = tf::Transform(quat, translasi);
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "base");
    broadcaster.sendTransform(current_frame);
    //==========end of base========
    
    // current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "head");
    // broadcaster.sendTransform(current_frame);


    //==========roda kanan========
    // quat = tf::Quaternion(0, 0, 0, 1);
    // translasi = tf::Vector3(lwheel, 0, 0);
    // src_point = tf::Transform(quat, translasi);
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "left_back_wheel");
    broadcaster.sendTransform(current_frame);
    //==========end of roda kanan========

    //==========roda kanan========
    // quat = tf::Quaternion(0, 0, 0, 1);
    // translasi = tf::Vector3(rwheel, 0, 0);
    // src_point = tf::Transform(quat, translasi);
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "right_back_wheel");
    broadcaster.sendTransform(current_frame);
    //==========end of roda kanan========
    // current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "left_front_wheel");
    // broadcaster.sendTransform(current_frame);
    // current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "right_front_wheel");
    // broadcaster.sendTransform(current_frame);
  
 
    // broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.0)),
    //     ros::Time::now(),
    //     "odom",
    //     "base"));
    /*
    ticks += 1;
    if (ticks >= 10) {
      ticks = 0;
    }
    */
    angle += degree/4;








    nav_msgs::Odometry odom;
    tf::StampedTransform current_frame;
    tf::Transform src_point;
    tf::Quaternion quat;
    tf::Vector3 translasi;

    // std::cout << x <<", "<< y <<"\n";
    //==========base========
    x=act_pos.linear.x;
    y=act_pos.linear.y;
    quat = tf::Quaternion(0, 0, x, 1);
    translasi = tf::Vector3( delta_x/dt, delta_y/dt, delta_th/dt);
    src_point = tf::Transform(quat, translasi);
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "base");
    odom_broadcaster.sendTransform(current_frame);
    //==========end of base========

    //==========roda kanan========
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "left_back_wheel");
    odom_broadcaster.sendTransform(current_frame);
    //==========end of roda kanan========

    //==========roda kiri========
    current_frame = tf::StampedTransform(src_point, ros::Time::now(),"odom", "right_back_wheel");
    odom_broadcaster.sendTransform(current_frame);
    //==========end of roda kiri========
    r.sleep();
    ros::spinOnce()
