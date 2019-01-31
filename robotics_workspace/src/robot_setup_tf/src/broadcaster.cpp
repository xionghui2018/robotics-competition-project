#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_setup_tf");
    ros::NodeHandle n;
    ros::Rate r(100);
    tf::TransformBroadcaster broadcaster;
    while (n.ok())
    {
        broadcaster.sendTransform(
            tf::StampedTransform(
                tf::Transform(tf::Quaternion(0, 0, 0, 1), //inital corrdiate axes
                tf::Vector3(0.1, 0.0, 0.2)), //offset 10cm in X, 20cm in Z direction
                ros::Time::now(), //time stamp
                "base_link", //parent node
                "base_laser")); //child node
        r.sleep();
    }   
    return 0;
}
