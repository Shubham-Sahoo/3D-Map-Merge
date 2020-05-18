#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>


void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg)
{
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "odom";
  transformStamped.child_frame_id = "world";
  transformStamped.transform.translation.x = msg->pose.position.x;
  transformStamped.transform.translation.y = msg->pose.position.y;
  transformStamped.transform.translation.z = msg->pose.position.z;
  //tf2::Quaternion q;
  
  //q.setRPY(msg->angular.x, msg->angular.y, msg->angular.z);//msg->theta);
  transformStamped.transform.rotation.x = msg->pose.orientation.x;
  transformStamped.transform.rotation.y = msg->pose.orientation.y;
  transformStamped.transform.rotation.z = msg->pose.orientation.z;
  transformStamped.transform.rotation.w = msg->pose.orientation.w;

  br.sendTransform(transformStamped);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_broadcaster2");

  ros::NodeHandle node;

  ros::Subscriber sub = node.subscribe("/icp_pose", 1000, &poseCallback);

  ros::spin();
  return 0;
};
