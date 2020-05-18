#include "ros/ros.h"
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "std_msgs/String.h"
#include <pcl/io/ply_io.h>
#include <iostream>
#include <sstream>
#include <pcl/common/transforms.h>




using namespace std;

ros::Publisher pub;


int main (int argc, char** argv)
{
  // Initialize ROS

  ros::init (argc, argv, "map_pub");
  ros::NodeHandle nh;
  cout<<"2";
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr transformed_cloud (new pcl::PCLPointCloud2 ());

  // Fill in the cloud data
  pcl::PLYReader reader;
  // Replace the path below with the path where you saved your file
  reader.read ("/home/shubham/Map-merge/src/map_merge/src/map1.ply", *cloud);

  std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd with the following fields: "
            << std::endl;
  /*for (std::size_t i = 0; i < cloud->points.size (); ++i)
    std::cout << "    " << cloud->points[i].x
              << " "    << cloud->points[i].y
              << " "    << cloud->points[i].z << std::endl;*/


  // Convert to ROS data type
  sensor_msgs::PointCloud2 output,output_tr;
  pcl_conversions::fromPCL(*cloud, output);
	output.header.frame_id="odom";

  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("/points_map", 100);
	ros::Rate loop_rate(10);
  while(nh.ok())
	{
  	pub.publish(output);
		ros::spinOnce();

    loop_rate.sleep();
	}

  return (0);
}








