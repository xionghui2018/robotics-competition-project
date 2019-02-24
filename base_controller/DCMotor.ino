#include <PID_v1.h>
int huoer = 2;//霍尔传感器计数
int PWMA = 10;
int PWMB = 11;// PWMA/B分别控制左/右电机
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;//对应L298N模块 IN1/2/3/4,用于控制电机方向与启停
int cishui = 80;//次数int 用于计数
double cishud;//次数double 用于计算转速
double input = 80;//pid的输入值 由转速赋给
double output = 80;//pid的输出值 由pid算法计算出 用于提供电机PWM[对应test的zkb(占空比)]
double rad=0;//转速 由次数除以33[30(减速比)*11(编码器缺口数)/10(每秒采样10次)]
unsigned long times = 0;
int taketime = 100;//时间变量 对应每秒采样10次 若需改动则转速计算式也要相应改动
boolean result;//pid算法的返回值 无用
double Setpoint;//pid的期望值(期望转速)
double Kp=0.2, Ki=3, Kd=0.02; //P/I/D的值 
PID myPID(&input, &output, &Setpoint, Kp, Ki, Kd, DIRECT); //pid算法

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(huoer,INPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);  
  attachInterrupt(digitalPinToInterrupt(huoer), count, FALLING);//中断函数 用于计数
  // Setpoint = 66;  //设置PID的输出值
   myPID.SetMode(AUTOMATIC);//设置PID为自动模式
   myPID.SetSampleTime(100);//设置PID采样频率为100ms
   myPID.SetOutputLimits(10, 250);  // 输出在40-240之间
}


void loop() {
 Setpoint = 66;  //填入的数字除以33即为转速/所需转速乘以33即为Setpoint
 if(Setpoint <80){
  myPID.SetTunings(2, 10, 0.02);
 }
 if(Setpoint <61){
  myPID.SetTunings(0.5, 6, 0.02);
 }
 if(Setpoint <41){
  myPID.SetTunings(0.2, 3, 0.02);
 }
  pid();
 }

void count() { 
  cishui++;
}

void pid(){
  input = cishud;
  result = myPID.Compute();//PID转换完成返回值为1
  analogWrite(PWMA,output);
  if (millis() >= times)
  { cishud = cishui;
    rad = cishud/33;
    test();
    times = millis()+taketime;
    cishui = 0;//输出速度结果后清零，记录下一秒的触发次数
  }
  }
void test(){
    Serial.println();
    Serial.print(output);
    Serial.println("-zkb");
    Serial.print(cishud);
    Serial.println("-cishu");
    Serial.print(rad);
    Serial.println("rad/s");
  }
