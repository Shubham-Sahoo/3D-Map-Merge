#include <iostream>
#include <sstream>

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/Odometry.h>


#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>



ros::Publisher pub;

static void convert(const nav_msgs::Odometry::ConstPtr& input)
{

	geometry_msgs::PoseWithCovarianceStamped output;
	output.header=input->header;
	output.pose.pose.position.x=input->twist.twist.linear.x;
	output.pose.pose.position.y=input->twist.twist.linear.y;
	output.pose.pose.position.z=input->twist.twist.linear.z;
	tf2::Quaternion q;
	q.setRPY(input->twist.twist.angular.x,input->twist.twist.angular.y,input->twist.twist.angular.z);
	q.normalize();
	output.pose.pose.orientation.x=q[0];
	output.pose.pose.orientation.y=q[1];
	output.pose.pose.orientation.z=q[2];
	output.pose.pose.orientation.w=q[3];

	output.pose.covariance=input->twist.covariance;

	pub.publish(output);
  
}

int main(int argc,char** argv)
{


	ros::init(argc,argv,"twist2q");
	ros::NodeHandle nh;

    pub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 1000);
    //ros::Rate loop_rate(10);
    
    ros::Subscriber map_sub = nh.subscribe("odom", 1000, convert);


    ros::spin();
    return 0;
}