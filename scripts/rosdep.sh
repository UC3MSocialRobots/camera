#!/bin/sh
# External, ROS and system package dependencies

PACKAGES="ffmpeg libavdevice53 libavcodec53 libswscale2"
sudo apt-get install $PACKAGES

# ar_pose
if [ -z $ROS_WORKSPACE ]; then
    echo ""
    echo "###########################################################"
    echo 'ERROR. $ROS_WORKSPACE missing, check .bashrc file. Exiting.'
    echo "###########################################################"
    echo ""
else
    #cd $ROS_WORKSPACE/src
    #git clone https://github.com/bosch-ros-pkg/usb_cam.git ##! usb_cam cant compile
fi
