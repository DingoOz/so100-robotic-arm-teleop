# so100-arm-teleop

This is a stand alone C++ application that allows for teleoperation of a 
leader / follower pair of SO-100 robotics arms. 

It does not rely on the URDF or concept of the arm itself but merely 
slaves 6 Feetech ST3215 servos hence additional applications may be useful.

It originally derived from a teleoperated robotic arm used on the robot
Perseus-v2 which competed in the Australian Rover Challenge 2025. 

# Background

This is a terminal based application for teleoperating of the S0-100 arm.

By default this will connect two arms connected via serial ports on the one machine.

It will display torque readings and position.

Calibration values for leader and follower arms can be saved to a .yaml file.

Always make sure all servos are on the same baud rate. 1M baud is able to be handled.

This has only been tested on Ubuntu 22.04 and 24.04 systems running on Intel and Arm hardware.

This is still an active WIP but currently useful.

# Build Instructions

```
mkdir build
```

```
cmake ..
make
```

# Use

You can run locally by running the application built from the build process.

Alternatively see below on how to use for teleoperation over a local network.

## To use over a network for teleoperation

We need to virtualise a remote serial port and present it as a local device. We can do this using the
Linux tool socat.

To install on Ubuntu

```
sudo apt install socat
```

#### First set up the Follower

This assumes serial port being used for the arm is /dev/ttyACM0.

```
socat TCP-LISTEN:7100,reuseaddr /dev/ttyACM0,b1000000,raw,echo=0
```

#### Second set up the Leader

This sets up a local file which is actually network connected to the remote serial port.
This assumes the remote machine has an IP Address of 192.168.1.15

```
socat PTY,link=/home/dingo/leader_follower,raw,echo=0 TCP:192.168.1.15:7100
```

Then run the application and the virtualised remote port should be detected automatically.

## TODO

- Handle rollover of values (joint #2 really needs this)
- Add PID to movements to reduce jerkiness
- Add ability to include 24 servos (second leader and second follower)
- Add additional diagnostic info

## DONE

- Add yaml config file loading
- Colour code torque values (mostly for gripper)
