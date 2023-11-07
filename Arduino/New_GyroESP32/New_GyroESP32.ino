#include <Wire.h> 
#include <EEPROM.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#define interruptPin 23

MPU6050 mpu;

typedef String str;

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
float yaw, offset = 0, offset1 = 0;
long t1 = 0, t3 = 0;
Quaternion q;
VectorFloat gravity;
float ypr[3];
String inString = "";

uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };


volatile bool mpuInterrupt = false;    
void dmpDataReady()  {
  mpuInterrupt = true;
}

void setup() { 
  Wire.begin();
  Wire.setClock(400000);
  
  Serial.begin(115200);
    
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
//UUS
//  mpu.setXAccelOffset(703);
//  mpu.setYAccelOffset(-4737);
//  mpu.setZAccelOffset(1189);
//  mpu.setXGyroOffset(216);
//  mpu.setYGyroOffset(12);
//  mpu.setZGyroOffset(15);
//ERO
  mpu.setXAccelOffset(689);
  mpu.setYAccelOffset(-4751);
  mpu.setZAccelOffset(1179);
  mpu.setXGyroOffset(203);
  mpu.setYGyroOffset(13);
  mpu.setZGyroOffset(12);
//ROS
//  mpu.setXAccelOffset(703);
//  mpu.setYAccelOffset(-4737);
//  mpu.setZAccelOffset(1189);
//  mpu.setXGyroOffset(216);
//  mpu.setYGyroOffset(12);
//  mpu.setZGyroOffset(15);
  
  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(interruptPin), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } 
}

void loop() { 
    if (!dmpReady) return;
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

    yaw = (ypr[0] * 180/M_PI); 
    float z = (yaw-offset)+offset1; 
    
    Serial.println(z);  
  while (Serial.available() > 0) {
    int inChar = Serial.read();

    if (inChar != '#') {
      inString += (char)inChar;
    }
    else {
      int dataIn = inString.toFloat();
      offset1=dataIn;
      offset = yaw;
      inString = "";
    }
  }
}
 
