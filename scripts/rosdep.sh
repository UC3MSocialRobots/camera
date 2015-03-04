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
#    cd $ROS_WORKSPACE
#    svn co https://svn.code.sf.net/p/bosch-ros-pkg/code/trunk/stacks/bosch_drivers/usb_cam
#    rospack profile
#	 rosmake usb_cam
fi
