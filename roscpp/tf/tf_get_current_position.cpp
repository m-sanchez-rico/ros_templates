#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tf2_listener");
  ros::NodeHandle node;

  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  // Loop to continuously get the current position of the base_link frame
  while (ros::ok())
  {
    geometry_msgs::TransformStamped transformStamped;
    try
    {
      // Get the transform from "base_link" to "map"
      transformStamped = tfBuffer.lookupTransform("map", "base_link", ros::Time(0));

      // Print the position of the transform
      ROS_INFO_STREAM("Current position of base_link: (" << transformStamped.transform.translation.x
                       << ", " << transformStamped.transform.translation.y << ", "
                       << transformStamped.transform.translation.z << ")");
    }
    catch (tf2::TransformException& ex)
    {
      ROS_WARN("%s", ex.what());
    }

    // Sleep for 1 second
    ros::Duration(1.0).sleep();
  }

  return 0;
}
