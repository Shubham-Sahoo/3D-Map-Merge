# Localisation and Map Merging


### Pre-requisite for SLAM simulation environment

# Table of Contents
- [Getting Started](#getting-started)
  - [Installation](#installation)
    - [Installation for Ubuntu 16.04 and ROS Kinetic](#installation-for-ubuntu-16.04-and-ros-kinetic)
  - [Run the Fouliex_Bot Gazebo Simulation](#run-the-avoidance-gazebosimulation)
- [Troubleshooting](#troubleshooting)
- [Advanced](#advanced)
  - [Message Flows](#message-flow)

# Getting Started

## Installation

### Installation for Ubuntu 16.04 and ROS Kinetic

This is a step-by-step guide to install and build all the prerequisites for running this module on Ubuntu 16.04. You might want to skip some of them if your system is already partially installed.


1. Add ROS to sources.list.

   ```bash
   echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list
   sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
   sudo apt update
   ```

2. Install gazebo with ROS.

   ```bash
   sudo apt install ros-kinetic-desktop-full

   # Source ROS
   source /opt/ros/kinetic/setup.bash
   ```

  Full installation of ROS Kinetic comes with Gazebo 7.

  If you are using different version of Gazebo,

  please make sure install ros-gazebo related packages

  For Gazebo 8,
  ```
  sudo apt install ros-kinetic-gazebo8-*
  ```
  For Gazebo 9,
  ```
  sudo apt install ros-kinetic-gazebo9-*
  ```

3. Initialize rosdep.

   ```bash
   rosdep init
   rosdep update
   ```

4. Install catkin and create your catkin workspace directory.

   ```bash
   sudo apt install python-catkin-tools
   mkdir -p ~/catkin_ws/src
   ```


5. Install module dependencies (pointcloud library and octomap).

   ```bash
   sudo apt install libpcl1 ros-kinetic-pcl-ros* ros-kinetic-yaml-*
   ```

6. Clone this repository in your catkin workspace in order to build the node.

   ```bash
   cd ~/catkin_ws/src
   git clone https://github.com/Shubham-Sahoo/Map-merge.git
   ```

7. Actually build the icp-matching node.

   ```bash
   catkin build -w ~/catkin_ws
   ```

   Note that you can build the node in release mode this way:

   ```bash
   catkin build -w ~/catkin_ws --cmake-args -DCMAKE_BUILD_TYPE=Release
   ```

8. Source the catkin setup.bash from your catkin workspace.

   ```bash
   source ~/catkin_ws/devel/setup.bash
	 ```

## Run the Fouliex_bot Gazebo Simulation

In the following section we guide you through installing and running a Gazebo simulation. 

### Build and Run the Simulator

9. Clone the repository and its submodules (it may take some time).

   ```bash
   cd ~/catkin_ws/src
	 git clone https://github.com/fouliex/MapAWorldWithSlamAndACustomRobot.git
   ```

10. Build the project

	 ```bash
	 cd ~/catkin_ws
	 catkin_make
	 source ~/catkin_ws/devel/setup.bash


Complete list is available on [Map_a_World_with_SLAM](https://github.com/Shubham-Sahoo/MapAWorldWithSlamAndACustomRobot.git)





