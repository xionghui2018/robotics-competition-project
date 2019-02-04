ROS中消息的种类及demo

```C++ 
    ROS_INFO_STREAM_ONCE("loop start");
    ROS_DEBUG_STREAM("DEBUG message.");
    ROS_INFO_STREAM("INFO message.");
    ROS_WARN_STREAM("WARN message.");
    ROS_ERROR_STREAM("ERROR message.");
    ROS_FATAL_STREAM("FATAL message.");
    ROS_INFO_STREAM_NAMED("named_msg", "INFO named message.");
    ROS_INFO_STREAM_THROTTLE(2, "INFO throttle message.");
```

