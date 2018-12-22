# roslaunch使用&学习小结

#### 简介
- ROS提供了一个同时启动节点管理器（master）和多个节点的途径，即使用启动文件（launch file）。事实上，在ROS功能包中，启动文件的使用是非常普遍的。任何包含两个或两个以上节点的系统都可以利用启动文件来指定和配置需要使用的节点。

#### 注意事项
- 通常的命名方案是以.launch作为启动文件的后缀，启动文件是XML文件。一般把启动文件存储在取名为launch的目录中。
- 每个XML文件都必须要包含一个根元素。根元素由一对launch标签定义：```<launch>... </launch>```元素都应该包含在这两个标签之内。

#### 标签
```<launch>```标签是任何roslaunch文件的根元素。它的唯一目的是作为其他元素的容器。其包含的元素有：

- ```<node>    ```启动节点 
- ```<param>   ``` 对参数服务器进行参数设置 
- ```<remap>   ``` 声明映射名 
- ```<machine> ``` 声明要启动的机器 
- ```<rosparam>```  使用rosparam文件启动设置ROS参数 
- ```<include> ``` 包含其他的roslaunch文件 
- ```<env>     ``` 为启动节点指定一个环境变量 
- ```<test>    ``` 启动一个测试节点 
- ```<arg>     ``` 声明一个提要 
- ```<group>   ``` 共享一个名称空间或重新映射组封闭元素

每个标签的格式至少包含下面三部分： 
1. ```pkg = "your package name"```
2. ```name = "your name" ```    //一般为可执行文件的名称 

3. ```type ="可执行文件的名称"```   （即在CMakeList.txt中的add_executable(node_name src/c++file.cpp)中的node_name） 

可选功能：

1. args 为运行时的参数, 示例： ```<arg name="a" default="1"/> <arg name="b" default="2" />```

    运行：
    
    -（未定义arg时） roslaunch beginner_tutorials add_two.launch a:=4 b:=5 

    -（定义arg后） roslaunch beginner_tutorials add_two.launch 或者roslaunch beginner_tutorials add_two.launch a:=4（只给a赋值，b不需要。此时修改值）

2. 运行后会保存至系统log文件中， 但不会显示在屏幕上， 使用```output```属性可以输出到屏幕上

    ```output = "screen"```
3. 如果想在节点启动时自动调用GDB调试器，需要添加```launch-prefix="xterm -e gdb --args"```  (prefix中文:字首。联想命令行)

