#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

MPU6050 mpu;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

typedef String str;

#define dRoda 6.1
#define perRotasi 2400 //jumlah pulsa 1 rotasi encoder
#define kelRoda (dRoda * PI) //keliling roda omni rotary
#define jarPerPulsa  kelRoda / perRotasi //jarak per pulsa omni encoder

#define jEncF 11.0 //jarak rotary depan ketitik tengah
#define jEncLR 34.0 //jarak rotary kiri kanan ketitik tengah

  
#define intPin1 19 //kiri
#define intPin2 5 //kanan 
#define intPin3 16 //depan
#define digPin1 15 //kiri
#define digPin2 18 //kanan
#define digPin3 17 //depan

#define interruptPin 23

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
float yaw, pitch, roll, offset = 0, offset1 = 0;
long t1 = 0, t3 = 0;
Quaternion q;
VectorFloat gravity;
float ypr[3];

int int1, int2, int3, frek1, frek2, frek3;
int _int1, _int2, _int3;
float jar1, jar2, jar3, jarX, jarY, Theta;

float vX, vY, dT;

long int count = 0;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  count++;
//  jar1 = jarPerPulsa * frek1;
//  jar2 = jarPerPulsa * frek2;
//  jar3 = jarPerPulsa * frek3; 
//  Theta += jarPerPulsa * (frek2 - frek1) / jEncLR * 180/PI;
//  jarY += jarPerPulsa * (frek1 + frek2) / 2.0;
//  jarX += jarPerPulsa * (frek3 - (frek2 - frek1) * jEncF / jEncLR);
//  
////  jarX += (cos(dT) * vX + sin(dT) * vY);
////  jarY += (-sin(dT) * vX + cos(dT) * vY);
////  jarX += vX;
////  jarY += vY;
//  
////  Theta += dT * 180/PI;
//
//  frek1 = 0;
//  frek2 = 0;
//  frek3 = 0;
  portEXIT_CRITICAL_ISR(&timerMux);
 
}

//void updateJarak() {
//  float vX, vY, T;
//
//  vX = jar3;   
//  vY = ;     
//   
//  jarX += (cos(radians(Theta)) * vX + sin(radians(Theta)) * vY);
//  jarY += (-sin(radians(Theta)) * vX + cos(radians(Theta)) * vY);
//}

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady()  {
  mpuInterrupt = true;
}

void setup() { 
  
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(115200);
  pinMode(intPin1, INPUT_PULLUP);
  pinMode(intPin2, INPUT_PULLUP);
  pinMode(intPin3, INPUT_PULLUP);
  pinMode(digPin1, INPUT_PULLUP);
  pinMode(digPin2, INPUT_PULLUP);
  pinMode(digPin3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(intPin1), interrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(intPin2), interrupt2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(intPin3), interrupt3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(digPin1), interrupt11, CHANGE);
  attachInterrupt(digitalPinToInterrupt(digPin2), interrupt21, CHANGE);
  attachInterrupt(digitalPinToInterrupt(digPin3), interrupt31, CHANGE);

  Serial.println("Coba Encoder");
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setRotation(2);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 50000, true );
  timerAlarmEnable(timer);

  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  mpu.setXAccelOffset(-1883);
  mpu.setYAccelOffset(-603);
  mpu.setZAccelOffset(665);
  mpu.setXGyroOffset(227);
  mpu.setYGyroOffset(-37);
  mpu.setZGyroOffset(-1); 
  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(interruptPin), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } 
}

void loop() {  
  getGyro();
//  if(_int1 != int1 || _int2 != int2 ||_int3 != int3){
//    
//    Serial.print(int1);
//    Serial.print(" ");
//    Serial.print(int2);
//    Serial.print(" ");
//    Serial.print(int3);
//    
//    Serial.println(); 
//    _int1 = int1;
//    _int2 = int2; 
//    _int3 = int3; 
//  } 

  dT = jarPerPulsa * (frek1 - frek2) / jEncLR;
  vY = jarPerPulsa * (frek1 + frek2) / 2.0;
  vX = jarPerPulsa * (frek3 - (frek2 - frek1) * jEncF / jEncLR);
  
  jarX += (cos(dT) * vX + sin(dT) * vY);
  jarY += (-sin(dT) * vX + cos(dT) * vY); 
  
  Theta += dT * 180/PI;

  frek1 = 0;
  frek2 = 0;
  frek3 = 0;

  oledClear();
  setCursor(0,0); oledPrint("DATA ENCODER");
  setCursor(0,1); oledPrint("encL:" + str(int1) + " jarX:" + str(jarX));
  setCursor(0,2); oledPrint("encR:" + str(int2) + " jarY:" + str(jarY));
  setCursor(0,3); oledPrint("encF:" + str(int3) + " Theta:" + str(Theta));
  setCursor(0,5); oledPrint("Gyro:" + str(yaw));

  
//  setCursor(0,1); oledPrint("encL:" + str(int1) + " jarL:" + str(jar1));
//  setCursor(0,2); oledPrint("encR:" + str(int2) + " jarR:" + str(jar2));
//  setCursor(0,3); oledPrint("encF:" + str(int3) + " jarF:" + str(jar3));
//  setCursor(0,5); 
  oledPrint(" Timer:" + str(count/20) + "s");
  
  oledDisplay();
  
  
}

void oledClear(){
  oled.clearDisplay();
}
void oledDisplay(){
  oled.display();
}
void setCursor(int x, int y){
//  oled.setCursor(x*12,y*19);
  oled.setCursor(x*6,y*11);
}
void oledPrint(String s){
  oled.print(s);
}

void interrupt1() {
  if (digitalRead(intPin1) != digitalRead(digPin1)) {
    int1++; 
    frek1++;
  }
  else {
    int1--; 
    frek1--;
  }
}
void interrupt2() {
  if (digitalRead(intPin2) != digitalRead(digPin2)) {
    int2++;
    frek2++;
  }
  else {
    int2--;
    frek2--;
  }
}
void interrupt3() {
  if (digitalRead(intPin3) != digitalRead(digPin3)) {
    int3++;
    frek3++;
  }
  else {
    int3--;
    frek3--;
  }
}

void interrupt11() {
  if (digitalRead(intPin1) == digitalRead(digPin1)) {
    int1++; 
    frek1++;
  }
  else {
    int1--; 
    frek1--;
  }
}
void interrupt21() {
  if (digitalRead(intPin2) == digitalRead(digPin2)) {
    int2++;
    frek2++;
  }
  else {
    int2--;
    frek2--;
  }
}
void interrupt31() {
  if (digitalRead(intPin3) == digitalRead(digPin3)) {
    int3++;
    frek3++;
  }
  else {
    int3--;
    frek3--;
  }
}

void getGyro(){   
  mpuInterrupt = false;
  fifoCount = mpu.getFIFOCount();
  
//  mpuIntStatus = mpu.getIntStatus();
  
  uint16_t MaxPackets = 20;
  if ((fifoCount % packetSize) || (fifoCount > (packetSize * MaxPackets)) || (fifoCount < packetSize)) { // we have failed Reset and wait till next time!
    mpuIntStatus = mpu.getIntStatus(); // reads MPU6050_RA_INT_STATUS       0x3A
    mpu.resetFIFO();// clear the buffer and start over
    mpu.getIntStatus(); // make sure status is cleared we will read it again.
  } else {
    while (fifoCount  >= packetSize) { // Get the packets until we have the latest!
      if (fifoCount < packetSize) break; // Something is left over and we don't want it!!!
      mpu.getFIFOBytes(fifoBuffer, packetSize); // lets do the magic and get the data
      fifoCount -= packetSize;
    } 

    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    float y = ypr[0] * 180/M_PI;
    pitch = ypr[2] * 180/M_PI;
    roll = ypr[1] * 180/M_PI; 
    
    if (fifoCount > 0) mpu.resetFIFO(); // clean up any leftovers Should never happen! but lets start fresh if we need to. this should never happen.

    yaw = (y-offset)+offset1;
     
  }  
}
void setGyro(float setoffset){ 
  while (!mpuInterrupt && fifoCount < packetSize) {} 
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount(); 
  mpu.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  
  float y = (ypr[0] * 180/M_PI);
  
  offset1=setoffset;
  offset = y;
}
