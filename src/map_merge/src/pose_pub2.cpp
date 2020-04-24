#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

ros::Publisher pub;

geometry_msgs::Twist data;
int main (int argc, char** argv)
{
  // Initialize ROS

  ros::init (argc, argv, "pose_pub2");
  ros::NodeHandle nh;

	data.linear.x=0;
	data.linear.y=0;
	data.linear.z=0;

	data.angular.x=0;
	data.angular.y=0;
	data.angular.z=0;

  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<geometry_msgs::Twist> ("pose2", 10);
	ros::Rate loop_rate(10);
  while(nh.ok())
	{
  	pub.publish(data);
		ros::spinOnce();

    loop_rate.sleep();
	}

  return (0);
}

