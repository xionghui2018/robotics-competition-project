# from: can't read /var/mail/xxx 解决方法 

在执行一个发包脚本的时候，遇到了如下问题：
`from: can't read /var/mail/scapy.all`
## 原因：脚本是没有问题的，但它并不是可以被python执行的可执行文件。
## 解决方法：
1. 使用python [脚本名字]命令执行脚本。
2. 在python文件中的开头加上：
`#!/usr/bin/env python`

## Referrence : （http://stackoverflow.com/questions/16069816/getting-python-error-from-cant-read-var-mail-bio）
## Referrence ： （https://www.cnblogs.com/qq952693358/p/6293087.html）
