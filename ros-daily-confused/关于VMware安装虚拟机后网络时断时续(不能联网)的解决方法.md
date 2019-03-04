# 关于VMware安装虚拟机后网络时断时续的解决方法

## 重装是没有用的！！！

## 解决办法

- 将NAT模式改为桥接模式（据dalao说，NAT模式更加复杂，桥接模式最为直接，但是需要配置）
`VMware 默认使用 net 地址转发模式。该模式相当于你在虚拟化一个操作系统的同时，虚拟了一个路由器（效率极其低下）。可以改用桥接模式。`
- 或者更暴力的，直接在虚拟机内将动态ip改为静态ip， IP复制VMware网络设置处的IP（我的为192.168.27.0）

## Referrence

1. https://www.cnblogs.com/maybe2030/p/4781555.html
2. https://superuser.com/questions/733166/no-internet-connection-in-virtual-machine-on-selecting-nat-in-vmware-workstation
3. https://blog.csdn.net/zhyulo/article/details/78730009
