#include <PID_v1.h>
int IN1_left = 31;
int IN2_left = 32;
int IN3_left = 33;
int IN4_left = 34;       //对应控制右轮L298N模块-1 IN1/2/3/4,用于控制电机方向与启停
int IN1_right = 41;
int IN2_right = 42;
int IN3_right = 43;
int IN4_right = 44;       //对应控制左轮L298N模块-2 IN1/2/3/4,用于控制电机方向与启停
double vel_in = 0.0;
double omg_in = 0.0;
void test();

class motor_settings
{
private:

public:

  double Kp = 0.0, Ki = 0.0, Kd = 0.0; //P/I/D的值
  int status = 0;
  int hall = 0;                //arduino上传入霍尔传感器计数的引脚
  int PWM = 0;                 //arduino上控制分别控制左/右电机的引脚
  int counter = 0;             //次数int 用于计数
  double counter_rotation = 0; //次数double 用于计算转速
  double input_PID = 80;       //次数double 用于计算转速
  double output_PID = 80;      //pid的输出值 由pid算法计算出 用于提供电机PWM[对应test的zkb(占空比)]
  double rad = 0;              //转速 由次数除以33[30(减速比)*11(编码器缺口数)/10(每秒采样10次)]
  double vel_out = 0.0;
  unsigned long times = 0;
  int take_time = 100;
  double SetPoint;
  
  PID myPID;
  
  

  void pid_process()
  {
    if (SetPoint < 80)
    {
      myPID.SetTunings(2, 10, 0.02);
    }
    if (SetPoint < 61)
    {
      myPID.SetTunings(0.5, 6, 0.02);
    }
    if (SetPoint < 41)
    {
      myPID.SetTunings(0.2, 3, 0.02);
    }
    input_PID = counter_rotation;
    myPID.Compute(); //PID转换完成返回值为1
    analogWrite(PWM, output_PID);
    if (millis() >= times)
    {
      counter_rotation = counter;
      rad = counter_rotation / 33;
      test();
      times = millis() + take_time;
      counter = 0; //输出速度结果后清零，记录下一秒的触发次数
    }
    else
    {
      Serial.print("k");
      delay(10);
    }
    
  }
  void vel_process()
  {
    if (status == 1 || status == 3)
    {
        vel_out = vel_in + omg_in * 15;
    }
    else if (status == 2 || status == 4)
    {
        vel_out = vel_in - omg_in * 15;
    }
  }
  void test()
  {
    Serial.println();
    Serial.print(output_PID);
    Serial.println("-zkb");
    Serial.print(counter_rotation);
    Serial.println("-cishu");
    Serial.print(rad);
    Serial.println("rad/s");
  }
  //用于在setup函数中设置各电机引脚状态
  motor_settings(int a, int b, int c) : hall(a), PWM(b), status(c), myPID(&input_PID, &output_PID, &SetPoint, Kp, Ki, Kd, DIRECT)
  { 
    myPID.SetMode(AUTOMATIC);                                     //设置PID为自动模式
    myPID.SetSampleTime(100);                                     //设置PID采样频率为100ms
    myPID.SetOutputLimits(10, 250);                               // 输出在40-240之间
                                                                  // Setpoint = 66;  //设置PID的输出值
    pinMode(hall,INPUT);
    pinMode(PWM,OUTPUT);



  }
};

motor_settings left_front_wheel(2, 10, 1);
motor_settings right_front_wheel(3, 11, 2);
motor_settings left_back_wheel(4, 12, 3);
motor_settings right_back_wheel(5, 13, 4);

void left_front_count()
{
  left_front_wheel.counter++;
}
void right_front_count()
{
  right_front_wheel.counter++;
}
void left_back_count()
{
  left_back_wheel.counter++;
}
void right_back_count()
{
  right_back_wheel.counter++;
}


void setup()
{
  Serial.begin(9600);
  pinMode(IN1_left, OUTPUT);
  pinMode(IN2_left, OUTPUT);
  pinMode(IN3_left, OUTPUT);
  pinMode(IN4_left, OUTPUT);

  pinMode(IN1_right, OUTPUT);
  pinMode(IN2_right, OUTPUT);
  pinMode(IN3_right, OUTPUT);
  pinMode(IN4_right, OUTPUT);

  digitalWrite(IN1_left, HIGH);
  digitalWrite(IN2_left, LOW);
  digitalWrite(IN3_left, HIGH);
  digitalWrite(IN4_left, LOW);

  digitalWrite(IN1_right, HIGH);
  digitalWrite(IN2_right, LOW);
  digitalWrite(IN3_right, HIGH);
  digitalWrite(IN4_right, LOW);
  attachInterrupt(digitalPinToInterrupt(left_front_wheel.hall), left_front_count, FALLING);
  attachInterrupt(digitalPinToInterrupt(right_front_wheel.hall), right_front_count, FALLING);
  attachInterrupt(digitalPinToInterrupt(left_back_wheel.hall), left_back_count, FALLING);
  attachInterrupt(digitalPinToInterrupt(right_back_wheel.hall), right_back_count, FALLING); //中断函数 用于0计数
}
void loop()
{
  vel_in = 8 * 3.14 * 2;
  omg_in = 0.3;
  left_front_wheel.vel_process();
  left_front_wheel.SetPoint = left_front_wheel.vel_out / (8 * 3.14) * 33; //填入的数字除以33即为转速/所需转速乘以33即为Setpoint_l
  left_front_wheel.pid_process();

  right_front_wheel.vel_process();
  right_front_wheel.SetPoint = right_front_wheel.vel_out / (8 * 3.14) * 33; //填入的数字除以33即为转速/所需转速乘以33即为Setpoint_l
  right_front_wheel.pid_process();

  left_back_wheel.vel_process();
  left_back_wheel.SetPoint = left_back_wheel.vel_out / (8 * 3.14) * 33; //填入的数字除以33即为转速/所需转速乘以33即为Setpoint_l
  left_back_wheel.pid_process();

  right_back_wheel.vel_process();
  right_back_wheel.SetPoint = right_back_wheel.vel_out / (8 * 3.14) * 33; //填入的数字除以33即为转速/所需转速乘以33即为Setpoint_l
  right_back_wheel.pid_process();

}
