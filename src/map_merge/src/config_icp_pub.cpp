#include <iostream>
#include <sstream>

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/PointCloud2.h>
#include <velodyne_pointcloud/point_types.h>
#include <velodyne_pointcloud/rawdata.h>

#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include "map_merge/ConfigICP.h"

static map_merge::ConfigICP data;


ros::Publisher pub;

int main(int argc,char** argv)
{


	ros::init(argc,argv,"config_pub");
	ros::NodeHandle nh;

    pub = nh.advertise<map_merge::ConfigICP>("config/icp", 10);
    ros::Rate loop_rate(10);
    data.header.frame_id="config";
	data.init_pos_gnss=0;
	data.x=0;
	data.y=0;
	data.z=0;
	data.roll=0;
	data.pitch=0;
	data.yaw=0;
	data.use_predict_pose=0;
	data.error_threshold=0.5;
	data.maximum_iterations=100;
	data.transformation_epsilon=0.01;
	data.max_correspondence_distance=1.0;
	data.euclidean_fitness_epsilon=0.1;
	data.ransac_outlier_rejection_threshold=1.0;
    while(nh.ok())
    {

    	pub.publish(data);
    	ros::spinOnce();
    	loop_rate.sleep();
    }

    return 0;
}