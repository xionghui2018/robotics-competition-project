在实际的项目中,实例化句柄时,经常会看到两种不同的写法
``` C++
ros::NodeHandle n; ros::NodeHandle nh("~");
```
这两种写法有什么不同呢?在demo.launch定义两个参数,一个全局`serial`他的数值是`5`,一个是局部的`serial`,他的数值是`10`.
```html
<launch>
	<!--全局参数serial-->
	<param name="serial" value="5" />
	<node name="name_demo" pkg="name_demo" type="name_demo" output="screen">
		<!--局部参数serial-->
		<param name="serial" value="10" />
	</node>
</launch>
```
以下是C++操作实例
```C++

#include <ros/ros.h>
int main(int argc, char **argv)
{
    int serial_num = -1;
    ros::init(argc, argv, "param_demo");

    ros::NodeHandle n;
    ROS_INFO("Global namespace");
    n.getParam("serial", serial_num);
    ROS_INFO_STREAM_ONCE("global_serial was "<<serial_num);
    n.getParam("param_demo/serial", serial_num);
    ROS_INFO_STREAM_ONCE("global_to_local_serial was "<<serial_num);


    ros::NodeHandle nh("~");
    ROS_INFO("local namespace");
    nh.getParam("/serial", serial_num);
    ROS_INFO_STREAM_ONCE("global_serial was "<<serial_num);
    nh.getParam("serial", serial_num);
    ROS_INFO_STREAM_ONCE("glbal_to_local_serial was "<<serial_num);

    ros::spin();
    return 0;
}

```
注意`getParam()`中的地址（第一个参数）表达