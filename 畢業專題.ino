#include <Servo.h>
Servo servoRight;
Servo servoLeft;
int trigPin = 4; // 超音波感測器 Trig 腳接 Arduino pin 11
int echoPin = 5; //超音波感測器 Echo 腳接 Arduino pin 12
long duration, cm ; //宣告計算距離時，需要用到的兩個實數
int photoresistor = A0; // 光敏電阻
int irSensorC = A1; //中紅外線感測器腳位
int irSensorL1 = A2; //左一紅外線感測器腳位
int irSensorR1 = A3; //右一紅外線感測器腳位
int irSensorL2 = A4; //左二紅外線感測器腳位
int irSensorR2 = A5; //右二紅外線感測器腳位
int C, L1, L2, R1, R2; //紅外線感測數值
int counter; // 跑流程
int shadow; //光電組
void setup()
{
Serial.begin(9600); //設定電腦和序列埠螢幕的傳輸速率 9600
bits/sec
servoRight.attach(12); //馬達
servoLeft.attach(13);
pinMode(trigPin, OUTPUT); //Arduino 對外啟動距離感測器
Trig 腳，射出超音波
pinMode(echoPin, INPUT); //超音波被障礙物反射後，
Arduino 讀取感測器 Echo 腳的時間差
pinMode(photoresistor, INPUT); //光電組
49
pinMode(irSensorC, INPUT); //Arduino 讀入 5 個感測器的狀態
pinMode(irSensorL1, INPUT);
pinMode(irSensorR1, INPUT);
pinMode(irSensorL2, INPUT);
pinMode(irSensorR2, INPUT);
counter = 0;
shadow = 1;
}
void loop(){
C = digitalRead(A1);
L1 = digitalRead(A2);
R1 = digitalRead(A3);
L2 = digitalRead(A4);
R2 = digitalRead(A5);
//-----------------------------------------執行動作
switch(counter)
{
 case 0:
 Photoresistor();
 break;
 case 1:
 IRsensor();
 break;
 case 2:
 Ultrasound();
 break;
}
}

50
//-----------------------------------------光敏電阻
int Photoresistor()
{
 if (shadow==1 && counter==0)
 {
 Stop;
 }
 shadow = digitalRead(A0);
 if (shadow == 0)
 counter = 1;
 return counter;
}
//-----------------------------------------紅外線感測器
int IRsensor()
{
 if(C == 0 && R1 == 1 && R2 == 1 && L1 == 1 && L2 == 1) //
連續曲線
 {
 Forward_S(1);
 }
 if(C == 1 && R1 == 1 && R2 == 1 && L1 == 0 && L2 == 1)
 {
 Left_S(1.25);
 }
 if(C == 1 && R1 == 1 && R2 == 1 && L1 == 0 && L2 == 0)
 {
 Left(1.25);
 }
 if(C == 0 && R1 == 1 && R2 == 1 && L1 == 0 && L2 == 1)
 {
 Left_S(1);
 }
 if(C == 1 && R1 == 0 && R2 == 1 && L1 == 1 && L2 == 1)
 {
 Right_S(1.25);
51
 }
 if(C == 1 && R1 == 0 && R2 == 0 && L1 == 1 && L2 == 1)
 {
 Right(1.25);
 }
 if(C == 0 && R1 == 0 && R2 == 1 && L1 == 1 && L2 == 1)
 {
 Right_S(1);
 }
 if(C == 1 && R1 == 1 && R2 == 1 && L1 == 1 && L2 == 0)
 {
 Left(2);
 }
 if(C == 1 && R1 == 1 && R2 == 0 && L1 == 1 && L2 == 1)
 {
 Right(2);
 }
 if(C == 0 && R1 == 0 && R2 == 1 && L1 == 0 && L2 == 1)
 {
 Forward_S(0.5);
 }
 if(C == 1 && R1 == 0 && R2 == 1 && L1 == 0 && L2 == 1)
 {
 Forward_S(0.5);
 }
 if(C == 1 && R1 == 1 && R2 == 1 && L1 == 1 && L2 == 1)
 {
 counter = 2;
 return counter;
 }
 if(C == 0 && R1 == 0 && R2 == 1 && L1 == 0 && L2 == 0)
 {
 Left_S(2);
 }
 if(C == 1 && R1 == 0 && R2 == 1 && L1 == 0 && L2 == 0)
 {
 Left_S(2);
 }
52
 if(C == 0 && R1 == 0 && R2 == 0 && L1 == 1&& L2 == 1)
 {
 Right_S(2);
 }
 }
//-----------------------------------------超聲波感測器
int Ultrasound()
{
 digitalWrite(trigPin, LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 pinMode(echoPin, INPUT);
 duration = pulseIn(echoPin, HIGH);
 cm = (duration/2) / 29.1;
 Serial.print(cm); //印出距離值 cm 在序列埠監控顯示器 單
位公分
 Serial.println(" cm");
 if(cm <= 10)
 {
 Semicircle();
 }
 else
 {
 Forward(1.5);
 }
 counter = 1;
 return counter;
}
53
//--------------------------------------馬達行動副程式
void Forward(int time) //車子前進子程式
{
 servoRight.writeMicroseconds(1450);
 servoLeft.writeMicroseconds(1640);
 delay(time);
}
void Forward_S(int time)//車子微前進子程式
{
 servoRight.writeMicroseconds(1490);
 servoLeft.writeMicroseconds(1590);
 delay(time);
}
void Back(int time) //車子後退子程式
{
 servoRight.writeMicroseconds(1700);
 servoLeft.writeMicroseconds(1300);
 delay(time);
}
void Stop(int time) //車子停止子程式
{
 servoRight.writeMicroseconds(1550);
 servoLeft.writeMicroseconds(1540);
 delay(time);
}
void Left(int time) //車子左轉子程式
{
 servoRight.writeMicroseconds(1380);
 servoLeft.writeMicroseconds(1390);
 delay(time);
}
void Left_S(int time) //車子微左轉子程式
{
 servoRight.writeMicroseconds(1300);
 servoLeft.writeMicroseconds(1525);
 delay(time);
}
void Right(int time) //車子右轉子程式
54
{
 servoRight.writeMicroseconds(1700);
 servoLeft.writeMicroseconds(1710);
 delay(time);
}
void Right_S(int time) //車子微右轉子程式
{
 servoRight.writeMicroseconds(1565);
 servoLeft.writeMicroseconds(1790);
 delay(time);
}
void Semicircle() //繞障礙物路徑
{
 Right(400);
 Forward(1000);
 Left(400);
 Forward(1100);
 Left(400);
 Forward(1000);
 Right(400);
}
