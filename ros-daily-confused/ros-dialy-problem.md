# Ubuntu上ROS的一些小坑

## personal enviornment status
- Windows 10 pro
- VMware14.X
- Ubuntu 16.04
- ROS : kinetic


## Attention
- 换源！！！换到中科大（ustc）或者是清华（Tsinghua）的，不然要慢死。特别是咱们大学生还有ipv6 #阴险
- 命令 ： ```sudo apt-get update ```; ```sudo apt-get upgrade```最好分开输入， 我一开始使用（```sudo apt-get update & upgrade```一直失败）

## Error1 :```E: Unable to locate package ros-kinetic-desktop-full ```

1. 检查是否正确添加bash和公钥， 以及update和upgrade
2. 多次重复尝试

##### 参考文档 ：https://answers.ros.org/question/235397/e-unable-to-locate-package-ros-kinetic-desktop-full/

## Error2 :  Read-only file system
#### 发生原因 ：

- 磁盘问题

#### 情况1：无法进行任何文件写入，包括Desktop
1. 打开terminal, 输入 : ```fsck -y /dev/sda1```
2. 一直按Y直到系统不问你问题
3. 重启，问题应该可以解决

#### 情况2：如果没有进行上述操作直接重启，开机界面出现下列情况 ：```The root filesystem on /dev/sda1 requires a manual fsck```（PS:我用的是3000*2000的13寸屏幕，看得我辣眼睛）

```
    dev/sda1: Inodes that were part of a corrupted orphan linked list found.
    /dev/sda1: UNEXPECTED INCONSISTENCY:; RUN fsck MANUALLY
            (i.e., without -a or -p options)
    fsck exited with status code 4
    The root filesystem on /dev/sda1 requires a manual fsck
    modprobe: module ehci-orion not found in modules.dep

    BusyBox v1.22.1 (Debian 1:1.22.0-9+deb8u1) built-in shell (ash)
    Enter 'help' for a list of built-in commands.
```

1. 输入 :  `fsck -y /dev/sda1`
2. 一直按Y直到系统不问你问题
3. 重启，问题应该可以解决

##### 参考文档 ： <https://blog.csdn.net/yjk13703623757/article/details/81055980>

## Error3 :```~./bashrc: No such file or directory 或者 bash : opt/ros/kinetic/setup.bash:```没有那个文件或目录

#### 发生原因：

配置重复？
#### 解决办法：
 在打开文件的最后找到`bash: /opt/ros/kinetic/setup.bash ` 删除重复的多余配置,如果没有多余项查看这句话拼写是否正确，或者与你的ros版本相称

1. 打开ternimal, 输入:```gedit ~/.bashrc ```（gedit可以随意换）
2. 删除无关/重复配置， 一般是在文件最后
3. save， 完成

##### 参考文档 ： https://blog.csdn.net/qq_35379989/article/details/78940961

## Error4 : 在IDE环境下（如VSCODE），提示 ```can not find the source file <ros/ros.h>```或者```找不到文件或目录 <ros/ros.h>```
1.找到ros中include的目录，一般为``` /opt/ros/kinetic/include ```
2.在vscode中打开```c_cpp_properties.json```
3.在```includePath```中添加```"/opt/ros/kinetic/include/*"```
4.save， 完成
书本背锅.`rxtools`不被`kinetic`包含，只存在于 `etectric`,`fuerte` 和 `groovy`

## ........未完待续，踩坑就更，大家也可以在issue处添加

## 转载自我的个人github：<https://github.com/lifuguan/Ubuntu-ROS-daily-porblem>
