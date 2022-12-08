# obstacle-avoider
This is ENPM808X assignment

## Dependencies
* ros2 galactic
* dolly robot (git clone https://github.com/chapulina/dolly.git)
* geometry_msgs
* sensor_msgs

## Build/run steps

### Create a workspace 

```
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
```
### Clone the repo into src folder
```
git clone https://github.com/guruadp/obstacle-avoider.git
```
### Building dolly packages
```
colcon build
```

### Build the package
```
colcon build --packages-select obstacle-avoider
```
Source the terminal

```
source /opt/ros/galactic/setup.bash
. install/setup.bash
```
## To run
```
ros2 launch obstacle-avoider obstacle_avoidance.launch.py 

```
### Open another terminal and run
```
ros2 launch obstacle-avoider robot.launch.py
```
### if gazebo doesnot open run this command and then re-run the previous command
```
. /usr/share/gazebo/setup.sh
```
