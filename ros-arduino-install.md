尽管网上有许多教程，但是我发现很多的表达都非常不清晰，甚至有些错误，在这里为大家纠正.
~~实名diss官方文档<http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup>~~
### 1.使用二进制/apt-get方式安装
```bash
sudo apt-get install ros-kinetic-rosserial-arduino
sudo apt-get install ros-kinetic-rosserial
```
### 2.复制到sketchbook的目录下
##### 注意：在Arduino目录下，我发现了一个叫sketchbook的文件夹，但实际目录并不是这个。请以`Arduino->File->Preferences->Sketchbook location:`中的地址为准

#### 2.1 错误操作
![sample](https://img-blog.csdn.net/20170715092632102?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZWxpb3Rfc2hhbw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

这时，官网推荐直接使用使用命令
```bash
cp -r ros_lib [你的sketchbook地址]
```

但是你会发现ros_lib中只有很少文件
![sample](https://github.com/lifuguan/Ubuntu-ROS-daily-porblem/blob/master/img/cp_ros_lib.jpg?raw=true)
当在Arduino IDE中编译的时候会发现错误```ros/node_handle.h No such file ```

#### 2.2 正确操作
此时你应该使用以下命令进行操作
```bash 
rosrun rosserial_arduino make_libraries.py [PathToYourSketchbookLibraries]
```
然后进入sketchbook中的ros_lib目录,可以发现出现了许多文件，且基本与ROS功能包相符合
![rosrun](https://github.com/lifuguan/Ubuntu-ROS-daily-porblem/blob/master/img/run_ros_lib.jpg?raw=true)

重新进行编译，编译通过

##### 参考：<https://answers.ros.org/question/96811/rosnode_handleh-no-such-file-error-in-arduino-hellow-world-tutorial/>