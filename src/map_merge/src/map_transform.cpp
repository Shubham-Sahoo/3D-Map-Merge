//#include <tf2_sensor_msgs.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.h>
#include <geometry_msgs/TransformStamped.h>
#include "ros/ros.h"
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "std_msgs/String.h"
#include <pcl/io/ply_io.h>
//#include <iostream>
#include <sstream>
#include <pcl/common/transforms.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/Twist.h>


using namespace std;
ros::Publisher pub;

void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
  // Create a container for the data.
  sensor_msgs::PointCloud2 output;
	static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped tr;
  geometry_msgs::TransformStamped tr_bs2;



  tf2::doTransform (*input, output, tr);
  //br.sendTransform(tr_bs2);
  // Publish the data.
  pub.publish (output);
}


int main (int argc, char** argv)
{
  // Initialize ROS

  ros::init (argc, argv, "map_transform");
  ros::NodeHandle nh;
  //cout<<"2";
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr transformed_cloud (new pcl::PCLPointCloud2 ());


  ros::Subscriber sub = nh.subscribe ("global_map", 1, cloud_cb);
  
	//ros::Subscriber sub2 = nh.subscribe ("tf", 1, cloud_cb);
  // Convert to ROS data type
  //sensor_msgs::PointCloud2 output_tr;




  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("output_trans", 1);

	//ros::Rate loop_rate(10);
  //while(nh.ok())
	//{
	//	pub.publish(output_tr);
	//	ros::spinOnce();

  //  loop_rate.sleep();
	//}
	ros::spin();
  return (0);
}

