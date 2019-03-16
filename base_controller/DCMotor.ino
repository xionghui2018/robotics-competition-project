#include <PID_v1.h>
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;//对应L298N模块 IN1/2/3/4,用于控制电机方向与启停

int huoer_l = 2;//霍尔传感器计数
int huoer_r = 3;//霍尔传感器计数
int PWM_L = 10;
int PWM_R = 11;// PWM_L/PWM_R分别控制左/右电机

int cishui_l = 80;//次数int 用于计数
double cishud_l;//次数double 用于计算转速
double input_l = 80;//pid的输入值 由转速赋给
double output_l = 80;//pid的输出值 由pid算法计算出 用于提供电机PWM[对应test的zkb(占空比)]
double rad_l=0;//转速 由次数除以33[30(减速比)*11(编码器缺口数)/10(每秒采样10次)]
unsigned long times_l = 0;
int taketime_l = 100;//时间变量 对应每秒采样10次 若需改动则转速计算式也要相应改动
double Setpoint_l;//pid的期望值(期望转速)
double Kp_l=0.2, Ki_l=3, Kd_l=0.02; //P/I/D的值 
PID myPID_l(&input_l, &output_l, &Setpoint_l, Kp_l, Ki_l, Kd_l, DIRECT); //pid算法

int cishui_r = 80;//次数int 用于计数
double cishud_r;//次数double 用于计算转速
double input_r = 80;//pid的输入值 由转速赋给
double output_r = 80;//pid的输出值 由pid算法计算出 用于提供电机PWM[对应test的zkb(占空比)]
double rad_r=0;//转速 由次数除以33[30(减速比)*11(编码器缺口数)/10(每秒采样10次)]
unsigned long times_r = 0;
int taketime_r = 100;//时间变量 对应每秒采样10次 若需改动则转速计算式也要相应改动
double Setpoint_r;//pid的期望值(期望转速)
double Kp_r=0.2, Ki_r=3, Kd_r=0.02; //P/I/D的值 
PID myPID_r(&input_r, &output_r, &Setpoint_r, Kp_r, Ki_r, Kd_r, DIRECT); //pid算法

boolean result;//pid算法的返回值 无用

double omg;
double v_l;
double v_r;
double v;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(huoer_l,INPUT);
  pinMode(huoer_r,INPUT);
  pinMode(PWM_L,OUTPUT);
  pinMode(PWM_R,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);  
  attachInterrupt(digitalPinToInterrupt(huoer_l), count_l, FALLING);//中断函数 用于计数
  attachInterrupt(digitalPinToInterrupt(huoer_r), count_r, FALLING);//中断函数 用于计数
   myPID_l.SetMode(AUTOMATIC);//设置PID为自动模式
   myPID_l.SetSampleTime(100);//设置PID采样频率为100ms
   myPID_l.SetOutputLimits(10, 250);  // 输出在10-250之间
   myPID_r.SetMode(AUTOMATIC);//设置PID为自动模式
   myPID_r.SetSampleTime(100);//设置PID采样频率为100ms
   myPID_r.SetOutputLimits(10, 250);  // 输出在10-250之间
}


void loop() {
  v = 8*3.14*2;
  omg = 0.3;
 v_l = v + omg*15;
 v_r = v - omg*15;
 Setpoint_l = v_l/(8*3.14)*33;  //填入的数字除以33即为转速/所需转速乘以33即为Setpoint_l
 pid_l();
 Setpoint_r = v_r/(8*3.14)*33;  //填入的数字除以33即为转速/所需转速乘以33即为Setpoint_l
 pid_r();
 }

void count_l() { 
  cishui_l++;
}
void count_r() { 
  cishui_r++;
}

void pid_l(){
  if(Setpoint_l <80){
  myPID_l.SetTunings(2, 10, 0.02);
 }
 if(Setpoint_l <61){
  myPID_l.SetTunings(0.5, 6, 0.02);
 }
 if(Setpoint_l <41){
  myPID_l.SetTunings(0.2, 3, 0.02);
 }
  input_l = cishud_l;
  result = myPID_l.Compute();//PID转换完成返回值为1
  analogWrite(PWM_L,output_l);
  if (millis() >= times_l)
  { cishud_l = cishui_l;
    rad_l = cishud_l/33;
    test_l();
    times_l = millis()+taketime_l;
    cishui_l = 0;//输出速度结果后清零，记录下一秒的触发次数
    }
  }
void pid_r(){
 if(Setpoint_r <80){
  myPID_r.SetTunings(2, 10, 0.02);
 }
 if(Setpoint_r <61){
  myPID_r.SetTunings(0.5, 6, 0.02);
 }
 if(Setpoint_r <41){
  myPID_r.SetTunings(0.2, 3, 0.02);
 }
  input_r = cishud_r;
  result = myPID_r.Compute();//PID转换完成返回值为1
  analogWrite(PWM_R,output_r);
  if (millis() >= times_r)
  { cishud_r = cishui_r;
    rad_r = cishud_l/33;
    test_r();
    times_r = millis()+taketime_r;
    cishui_r = 0;//输出速度结果后清零，记录下一秒的触发次数
    }
  }
void test_l(){
    Serial.println();
    Serial.print(output_l);
    Serial.println("-zkb");
    Serial.print(cishud_l);
    Serial.println("-cishu");
    Serial.print(rad_l);
    Serial.println("rad_l/s");
  }
void test_r(){
    Serial.println();
    Serial.print(output_r);
    Serial.println("-zkb");
    Serial.print(cishud_r);
    Serial.println("-cishu");
    Serial.print(rad_r);
    Serial.println("rad_r/s");
  }
