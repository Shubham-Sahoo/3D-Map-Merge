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
	output.pose.pose.position.x=input->pose.pose.position.x;
	output.pose.pose.position.y=input->pose.pose.position.y;
	output.pose.pose.position.z=input->pose.pose.position.z;
	output.pose.pose.orientation.x=input->pose.pose.orientation.x;
	output.pose.pose.orientation.y=input->pose.pose.orientation.y;
	output.pose.pose.orientation.z=input->pose.pose.orientation.z;
	output.pose.pose.orientation.w=input->pose.pose.orientation.w;

	output.pose.covariance=input->pose.covariance;

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
