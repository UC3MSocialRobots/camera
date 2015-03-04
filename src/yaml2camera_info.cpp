/*!
  \file        yaml2camera_info.cpp
  \author      Arnaud Ramey <arnaud.a.ramey@gmail.com>
                -- Robotics Lab, University Carlos III of Madrid
  \date        2014/8/28

________________________________________________________________________________

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
________________________________________________________________________________

A small executable to read a calibration file
and publish the associated CameraInfo.

\section Parameters
  - \b "~file_name"
        [string] (default: "")
        The path to the YAML or INI calibration file.
  - \b "~camera_name"
        [string] (default: "camera")
        The name of the camera device according to URDF.
  - \b "~topic_name"
        [string] (default: "camera_info")
        The topic name where the CameraInfo will be pulbished.
  - \b "~rate"
        [int, Hertz] (default: 5)
        The publish rate, in Hertz.

\section Subscriptions
    None

\section Publications
  - \b "{topic_name}"
        [sensor_msgs::CameraInfo]
        The read CameraInfo
 */
#include <ros/ros.h>
#include <camera_calibration_parsers/parse.h>
#include <camera_calibration_parsers/parse_ini.h>
#include <camera_calibration_parsers/parse_yml.h>
#include <boost/algorithm/string/predicate.hpp>

int main(int argc, char** argv) {
  ros::init(argc, argv, "2camera_info");
  ros::NodeHandle nh_public, nh_private("~");
  std::string file_name = "", camera_name = "camera", topic_name = "camera_info";
  int rate_freq = 10;
  // read params
  nh_private.param("file_name", file_name, file_name);
  nh_private.param("camera_name", camera_name, camera_name);
  nh_private.param("topic_name", topic_name, topic_name);
  nh_private.param("rate", rate_freq, rate_freq);

  if (file_name.size() == 0) {
    ROS_ERROR("You need to specify the file_name");
    ros::shutdown();
  }
  // parse camera info
  sensor_msgs::CameraInfo cam_info;
  bool parse_success = false;
  parse_success = (boost::iends_with(file_name, ".ini")
                   && camera_calibration_parsers::readCalibrationIni
                   (file_name, camera_name, cam_info));
  parse_success = (boost::iends_with(file_name, ".yml") || boost::iends_with(file_name, ".yaml"))
                  && camera_calibration_parsers::readCalibrationYml
                  (file_name, camera_name, cam_info);
  if (!parse_success){
    ROS_ERROR("Could not parse calibration file '%s'", file_name.c_str());
    ros::shutdown();
  }
  // advertize
  ros::Publisher pub = nh_public.advertise<sensor_msgs::CameraInfo>
                       (topic_name, 1, true);
  // publish
  ros::Rate rate(rate_freq);
  while (ros::ok()) {
    cam_info.header.stamp = ros::Time::now();
    pub.publish(cam_info);
    ros::spinOnce();
    rate.sleep();
  }
} // end main()
