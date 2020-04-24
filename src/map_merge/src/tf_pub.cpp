#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>


void poseCallback(const geometry_msgs::TwistConstPtr& msg)
{
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "map";
  transformStamped.child_frame_id = "odom";
  transformStamped.transform.translation.x = msg->linear.x;
  transformStamped.transform.translation.y = msg->linear.y;
  transformStamped.transform.translation.z = 0.0;
  tf2::Quaternion q;
  
  q.setRPY(msg->angular.x, msg->angular.y, msg->angular.z);//msg->theta);
  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();

  br.sendTransform(transformStamped);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_broadcaster1");

  ros::NodeHandle node;

  ros::Subscriber sub = node.subscribe("/pose1", 10, &poseCallback);

  ros::spin();
  return 0;
};
