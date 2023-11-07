#include <LiquidCrystal.h>
#include <MsTimer2.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "initGPIO.h"
#include "initVariable.h"

#define SerialCamera Serial1
#define SerialCoach Serial2
#define SerialJoystick Serial2
#define SerialGyro Serial3

// SoftwareSerial SerialJoystick(A8, -1); // RX, TX

LiquidCrystal lcd(lcdRS, lcdEN, lcdD4, lcdD5, lcdD6, lcdD7); 

void setup() {
  EEPROM.get(addEE, EE);

  if(pilihRobotUUS){
    enableRobot = 1;
    EE.enableRobot = 1;
    EEPROM.put(addEE, EE);
  } else if(pilihRobotERO){
    enableRobot = 2;
    EE.enableRobot = 2;
    EEPROM.put(addEE, EE);
  } else if(pilihRobotROS){
    enableRobot = 3;
  } else {
    enableRobot = EE.enableRobot;
  }

  if(enableRobot == uus){
    dRoda = 6.4; //diameter omni rotary uus
    offsetGyro = 180; 
    derM1 = 40;
    derM2 = 360-40;
    derM3 = 180+40;
    derM4 = 180-40;
    
    pwmM4_1 = 12; //motor kiri depan UUS
    pwmM4_2 = 13; //motor kiri depan UUS

    
  } else {
    dRoda = 6.4; //diameter omni rotary ero / ros
    offsetGyro = 0;
    derM1 = 30;
    derM2 = 270;
    derM3 = 150;
    derM4 = 0;
    
    pwmM4_1 = -1; //motor dribble ERO/ROS
    pwmM4_2 = -1; //motor dribble ERO/ROS

  }

  initTimer();
  initMotor();
  initEncoder();
  initGPIO();
  stopTendang();

  perRotasi = 14; //jumlah pulsa 1 rotasi encoder
  kelRoda = (dRoda * 22 / 7); //keliling roda omni rotary
  jarPerPulsa = kelRoda / perRotasi; //jarak per pulsa omni encoder

  Serial.begin(9600);
  SerialCamera.begin(9600); 
  SerialGyro.begin(115200); 
  SerialCoach.begin(9600); 
  SerialJoystick.begin(9600);  

  lcd.begin(20,4);

  dribble(-255);
  delay(1000);
  dribble(0);
}

void loop() {

  menuAwal();

  // cursor(0,0); 
  // print("Detik Main:" + str(detikMain/convertInterrupt));

  // cursor(0,1);
  // print("Encoder1:" + str(countEncoder1) + " " + str(digitalRead(intPin1)));
  // cursor(0,2);
  // print("Encoder2:" + str(countEncoder2) + " " + str(digitalRead(intPin2)));
  // cursor(0,3);
  // print(str(C) + "" + str(U) + "" + str(D) + "" + str(P) + "" + str(M) + "" + str(O));
}
