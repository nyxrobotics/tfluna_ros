#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string>
#include <sensor_msgs/Range.h>

namespace benewake
{
class Tfluna
{
public:
  Tfluna(const std::string& portname, int baudrate);
  ~Tfluna(){};
  float getDist();
  void closePort();

  unsigned char dataBuf_[7];

private:
  std::string portname_;
  int baudrate_;
  int serial_;

  bool readData(unsigned char* _buf, int _nRead);
};
}  // namespace benewake
