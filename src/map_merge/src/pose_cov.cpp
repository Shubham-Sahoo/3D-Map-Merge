#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/PointCloud2.h>
#include <velodyne_pointcloud/point_types.h>
#include <velodyne_pointcloud/rawdata.h>
#include <Eigen/Dense>


#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/voxel_grid.h>

#include "map_merge/ConfigICP.h"

#include "map_merge/ICPStat.h"


ros::Publisher pub;

int main(int argc,char** argv)
{


	ros::init(argc,argv,"covariance_pose");
	ros::NodeHandle nh;

    pub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 10);

    ros::Rate loop_rate(10);

	geometry_msgs::PoseWithCovarianceStamped data;	
	


    data.header.frame_id="velodyne";
	data.pose.pose.position.x=0;
	data.pose.pose.position.y=0;
	data.pose.pose.position.z=0;
	data.pose.pose.orientation.x=0;
	data.pose.pose.orientation.y=0;
	data.pose.pose.orientation.z=0;
	data.pose.pose.orientation.w=1;

	/*double t[6][6];
	t[0][0]=1;t[0][1]=0;t[0][2]=0;t[0][3]=0;t[0][4]=0;t[0][5]=0;
	t[1][0]=0;t[1][1]=1;t[1][2]=0;t[1][3]=0;t[1][4]=0;t[1][5]=0;
	t[2][0]=0;t[2][1]=0;t[2][2]=1;t[2][3]=0;t[2][4]=0;t[2][5]=0;
	t[3][0]=0;t[3][1]=0;t[3][2]=0;t[3][3]=1;t[3][4]=0;t[3][5]=0;
	t[4][0]=0;t[4][1]=0;t[4][2]=0;t[4][3]=0;t[4][4]=1;t[4][5]=0;
	t[5][0]=0;t[5][1]=0;t[5][2]=0;t[5][3]=0;t[5][4]=0;t[5][5]=1;*/

	boost::array<double, 36> t = {1,0,0,0,0,0,
								0,1,0,0,0,0,
								0,0,1,0,0,0,
								0,0,0,1,0,0,
								0,0,0,0,1,0,
								0,0,0,0,0,1};
	data.pose.covariance=t;

    while(nh.ok())
    {

    	pub.publish(data);
    	ros::spinOnce();
    	loop_rate.sleep();
    }

    return 0;
}