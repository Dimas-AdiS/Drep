#define pinRobotUUS A0
#define pinRobotERO A1
#define pinRobotROS A2

#define pinDribble A3

#define pinProxy1 A4
#define pinProxy2 A5
#define pinProxy3 A6
#define pinProxy4 A7
#define pinProxy5 A10
#define pinProxy6 A11
#define pinProxy7 A12
#define pinProxy8 A13
#define pinProxy9 A14

#define proxy1 !digitalRead(pinProxy1)
#define proxy2 !digitalRead(pinProxy2)
#define proxy3 !digitalRead(pinProxy3)
#define proxy4 !digitalRead(pinProxy4)
#define proxy5 !digitalRead(pinProxy5)
#define proxy6 !digitalRead(pinProxy6)
#define proxy7 !digitalRead(pinProxy7)
#define proxy8 !digitalRead(pinProxy8)
#define proxy9 !digitalRead(pinProxy9)

#define pilihRobotUUS digitalRead(pinRobotUUS)
#define pilihRobotERO digitalRead(pinRobotERO)
#define pilihRobotROS digitalRead(pinRobotROS)


#define intPin1 3   //uus kiri, ero ros kanan
#define intPin2 2   //uus kanan, ero ros kiri
#define intPin3 21  //uus belakang, ero ros depan
#define digPin1 22  //uus kanan, ero ros kiri
#define digPin2 24  //uus kanan, ero ros kiri
#define digPin3 28  //uus belakang, ero ros depan

#define pinC 41
#define pinP 33
#define pinM 35
#define pinD 37
#define pinU 39
#define pinO 31

#define C digitalRead(pinC)
#define M digitalRead(pinM)
#define P digitalRead(pinP)
#define U digitalRead(pinU)
#define D digitalRead(pinD)
#define O digitalRead(pinO)

#define jarD digitalRead(pinDribble)

#define pwmM1_1 4  //motor kanan depan UUS //motor kanan ROS ERO
#define pwmM1_2 5  //motor kanan depan UUS //motor kanan ROS ERO
#define pwmM2_1 6  //motor kanan belakang UUS //motor belakang ROS ERO
#define pwmM2_2 7  //motor kanan belakang UUS //motor belakang ROS ERO
#define pwmM3_1 8  //motor kiri belakang UUS //motor kiri ROS ERO
#define pwmM3_2 9  //motor kiri belakang UUS //motor kiri ROS ERO
// #define pwmM4_1 12 //motor kiri depan UUS
// #define pwmM4_2 13 //motor kiri depan UUS

#define pwmD_1 12
#define pwmD_2 13

#define pinEnableMotor 10  //PIN enableMotor

#define enableMotor digitalWrite(pinEnableMotor, HIGH)
#define disableMotor digitalWrite(pinEnableMotor, LOW)

#define pwmDL_1 2   //motor dribble kiri ROS //motor dribble ERO
#define pwmDL_2 32  //motor dribble kiri ROS //motor dribble ERO
#define pwmDR_1 3   //motor dribble kanan ROS
#define pwmDR_2 30  //motor dribble kanan ROS

#define lcdRS 34
#define lcdEN 36
#define lcdD4 38
#define lcdD5 40
#define lcdD6 42
#define lcdD7 44


#define pinTendangSlow 45
#define pinTendangFull 47
// #define pinTendangSlow 20
// #define pinTendangFull 26
// #define pinTendangSlow 27
// #define pinTendangFull 29


void initGPIO() {
  pinMode(pinProxy1, INPUT_PULLUP);
  pinMode(pinProxy2, INPUT_PULLUP);
  pinMode(pinProxy3, INPUT_PULLUP);
  pinMode(pinProxy4, INPUT_PULLUP);
  pinMode(pinProxy5, INPUT_PULLUP);
  pinMode(pinProxy6, INPUT_PULLUP);
  pinMode(pinProxy7, INPUT_PULLUP);
  pinMode(pinProxy8, INPUT_PULLUP);
  pinMode(pinProxy9, INPUT_PULLUP);

  pinMode(pinC, INPUT_PULLUP);
  pinMode(pinM, INPUT_PULLUP);
  pinMode(pinP, INPUT_PULLUP);
  pinMode(pinU, INPUT_PULLUP);
  pinMode(pinD, INPUT_PULLUP);
  pinMode(pinO, INPUT_PULLUP);
  pinMode(pinRobotUUS, INPUT_PULLUP);
  pinMode(pinRobotERO, INPUT_PULLUP);
  pinMode(pinRobotROS, INPUT_PULLUP);
  pinMode(pinDribble, INPUT_PULLUP);
  pinMode(pinTendangSlow, OUTPUT);
  pinMode(pinTendangFull, OUTPUT);
  digitalWrite(pinTendangSlow, LOW);
  digitalWrite(pinTendangFull, LOW);
}
