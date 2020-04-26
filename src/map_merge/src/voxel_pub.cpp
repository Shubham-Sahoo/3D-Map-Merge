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
#include <pcl/filters/voxel_grid.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>


using namespace std;

ros::Publisher pub;

void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
  // Create a container for the data.
  sensor_msgs::PointCloud2 output;
	//static tf2_ros::TransformBroadcaster br;
  //geometry_msgs::TransformStamped tr;
  //geometry_msgs::TransformStamped tr_bs2;
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());
	pcl_conversions::toPCL(*input,*cloud);
	


    //pcl::PCLPointCloud2 pcl_pc2;
    
    //pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    //pcl::fromPCLPointCloud2(pcl_pc2,*temp_cloud);

	pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  sor.setInputCloud (cloud);
  sor.setLeafSize (0.1f, 0.1f, 0.1f);
  sor.filter (*cloud_filtered);

  pcl_conversions::fromPCL(*cloud_filtered, output);

	/*tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);
	try
	{
		//tfBuffer.waitForTransform("/base_link2", "/base_link1", ros::Time(0), ros::Duration(3.0));
  	tr = tfBuffer.lookupTransform("base_link2", "base_link1", ros::Time(0),ros::Duration(3.0));
	}
    catch (tf2::TransformException &ex) {
      ROS_WARN("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

	
	tr_bs2.header.stamp = ros::Time::now(); 
  tr_bs2.header.frame_id = "odom" ;
  //tr_bs2.child_frame_id = "";
  tr_bs2.transform.translation.x = -1; 
  tr_bs2.transform.translation.y = 0; 
  tr_bs2.transform.translation.z = 0; 
  tf2::Quaternion q;
  
  q.setRPY(0,0,0);//msg->theta);
  tr_bs2.transform.rotation.x = q.x();
  tr_bs2.transform.rotation.y = q.y();
  tr_bs2.transform.rotation.z = q.z();
  tr_bs2.transform.rotation.w = q.w();
	*/
  //tf2::doTransform (*input, output, tr);
  //br.sendTransform(tr_bs2);
  // Publish the data.
  pub.publish (output);
}


int main (int argc, char** argv)
{
  // Initialize ROS

  ros::init (argc, argv, "map_filter");
  ros::NodeHandle nh;
  //cout<<"2";
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr transformed_cloud (new pcl::PCLPointCloud2 ());


  ros::Subscriber sub = nh.subscribe ("camera/depth/points", 10, cloud_cb);
  
	//ros::Subscriber sub2 = nh.subscribe ("tf", 1, cloud_cb);
  // Convert to ROS data type
  //sensor_msgs::PointCloud2 output_tr;




  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("points_raw", 10);

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


