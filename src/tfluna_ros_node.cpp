#include "tfluna.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tfluna_ros_node");
  ros::NodeHandle nh("~");
  std::string frame_id = "tfluna";
  std::string portname;
  int baud_rate;
  benewake::Tfluna* tfluna_obj;

  nh.param("serial_port", portname, std::string("/dev/ttyUSB0"));
  nh.param("baud_rate", baud_rate, 115200);

  tfluna_obj = new benewake::Tfluna(portname, baud_rate);
  ros::Publisher pub_range = nh.advertise<sensor_msgs::Range>("range", 5, true);
  sensor_msgs::Range tfluna_range;
  tfluna_range.radiation_type = sensor_msgs::Range::INFRARED;
  tfluna_range.field_of_view = 0.0349066;  // In degrees it is 2 is it's converted into radians.
  tfluna_range.min_range = 0.2;
  tfluna_range.max_range = 8;
  tfluna_range.header.frame_id = frame_id;
  float dist = 0;
  ROS_INFO_STREAM("Start processing ...");

  while (ros::master::check() && ros::ok())
  {
    ros::spinOnce();
    dist = tfluna_obj->getDist();
    if (dist == -1.0)
    {
      ROS_ERROR_STREAM("Failed to read data");
    }
    else
    {
      tfluna_range.range = dist;
      tfluna_range.header.stamp = ros::Time::now();
      pub_range.publish(tfluna_range);
    }
  }
  tfluna_obj->closePort();
}
