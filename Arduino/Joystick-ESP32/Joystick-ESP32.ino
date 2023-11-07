#include <Ps3Controller.h> 
#include <EEPROM.h>
#include "Variabel.h" 

#define ledPin 2
#define pinSetting 0

#define ledON digitalWrite(ledPin, HIGH)
#define ledOFF digitalWrite(ledPin, LOW)

//char *MAC = "78:dd:08:65:53:bb"; //UUS
//char *MAC = "78:dd:08:65:53:ba"; //ERO
char *MAC = "40:22:d8:5f:0b:26"; //ROS
//char *MAC = "ac:67:b2:2d:22:ae"; //stikku 
//40:22:d8:5f:0b:26
 

void onConnect() {
  Serial.println("Connected!.");  
  Ps3.setPlayer(1);
  ledON;
}

void notify() {  
  xR =Ps3.data.analog.stick.rx;  // Right stick - x axis
  yR =-Ps3.data.analog.stick.ry;  // Right stick  - y axis
  xL =Ps3.data.analog.stick.lx;  // Left stick - x axis
  yL =-Ps3.data.analog.stick.ly;  // Left stick  - y axis 

  X = Ps3.data.button.cross;
  S = Ps3.data.button.square;
  T = Ps3.data.button.triangle;
  C = Ps3.data.button.circle;

  up = Ps3.data.button.up;
  dw = Ps3.data.button.down;
  lf = Ps3.data.button.left;
  rg = Ps3.data.button.right;
  
  L1 = Ps3.data.button.l1;
  L2 = Ps3.data.button.l2;
  L3 = Ps3.data.button.l3; 
  R1 = Ps3.data.button.r1;
  R2 = Ps3.data.button.r2;
  R3 = Ps3.data.button.r3;  
  
  AL2 = Ps3.data.analog.button.l2; 
  AR2 = Ps3.data.analog.button.r2;
  
  SELECT = Ps3.data.button.select;
  START = Ps3.data.button.start; 

  BATT = Ps3.data.status.battery;
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(pinSetting, INPUT_PULLUP);
  
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  
  bool initPS3 = Ps3.begin(MAC);

  if(initPS3==1){
    Serial.println("ESP32 Berhasil Inisialisasi");
  } else{
    Serial.println("ESP32 Gagal Inisialisasi");
  }
  
  EEPROM.begin(1023); 
  EEPROM.get(addEE, EE); 
  
  ledON;
  delay(200);
  ledOFF;
  delay(200);
}

void loop() { 
//  if(SELECT){setMode = 1;} 
//  if(START){setMode = 0;} 
  if(digitalRead(pinSetting) == 0){
    setMode = !setMode; delay(300);
  }
  
  if(setMode){ 
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 600) {  
      ledON;
      previousMillis = currentMillis;
    }else if (currentMillis - previousMillis >= 400) {  
      ledOFF;
    }
  } 

  if(R2==1){modeSpeed=2;}
  else if(L2==1){modeSpeed=0;}
  else {modeSpeed=1;} 
  
  if(setMode){
    setValue[0] = EE.SPEED[modeSpeed];
    setValue[1] = EE.SPEEDR[modeSpeed]; 

//    unsigned long currentMillis1 = millis();
//    if (currentMillis1 - previousMillis1 >= 300) {   
//      previousMillis1 = currentMillis1;
//    
//      Serial.print(str("SPEED ") + str(tampilModeSpeed[modeSpeed]) + setValue[0] + str(" ROTASI : ") + setValue[1]);
//  
//      Serial.print(" BATT : ");
//      if(BATT == ps3_status_battery_charging )      {Serial.print("charging ");}
//      else if(BATT == ps3_status_battery_full )     {Serial.print("FULL ");}
//      else if(BATT == ps3_status_battery_high )     {Serial.print("HIGH ");}
//      else if(BATT == ps3_status_battery_low)       {Serial.print("LOW ");}
//      else if(BATT == ps3_status_battery_dying )    {Serial.print("DYING ");}
//      else if(BATT == ps3_status_battery_shutdown ) {Serial.print("SHUTDOWN ");}
//      else {Serial.print("UNDEFINED ");}
//      Serial.println(); 
//    }
    
    if(up){
      changeValue = 1;
      setValue[0]++;
    }else if(dw){
      changeValue = 1;
      setValue[0]--;
    }

    if(rg){
      changeValue = 1;
      setValue[1]++;
    }else if(lf){
      changeValue = 1;
      setValue[1]--;
    }
  }

  if(changeValue == 1){
    changeValue = 0;
    EE.SPEED[modeSpeed] = setValue[0];
    EE.SPEEDR[modeSpeed] = setValue[1];  
    
    EEPROM.put(addEE, EE); 
    EEPROM.commit();

    delay(2);
  } 
  
  yL = constrain(yL,-127,127);
  xL = constrain(xL,-127,127);
  yR = constrain(yR,-127,127);
  xR = constrain(xR,-127,127); 
  
  if(modeSpeed==2){
    SPEED = map(AR2, 0, 255, EE.SPEED[1], EE.SPEED[2]);
    SPEEDR = map(AR2, 0, 255, EE.SPEEDR[1], EE.SPEEDR[2]);
  } else if(modeSpeed==0){
    SPEED = map(AL2, 0, 255, EE.SPEED[1], EE.SPEED[0]); 
    SPEEDR = map(AL2, 0, 255, EE.SPEEDR[1], EE.SPEEDR[0]); 
  } else{
    SPEED = EE.SPEED[1];
    SPEEDR = EE.SPEEDR[1];
  }
  
  pwmY = map(yL,-127, 127, -SPEED, SPEED);
  pwmX = map(xL,-127, 127, -SPEED, SPEED); 
  pwmW = map(xR,-127, 127, -SPEEDR, SPEEDR);  

  if(!setMode){ 
//    ledON;
    if(up){
      pwmY = SPEED;
    }
    if(dw){
      pwmY = -SPEED;
    }
    if(rg){
      pwmX = SPEED;
    }
    if(lf){
      pwmX = -SPEED;
    }
  }
   
  
  if(SPEED > SPEEDR){
    maxPWM = SPEED;
  } else {
    maxPWM = SPEEDR;
  }
   
  maxPWM = constrain(maxPWM, MINPWM, MAXPWM); 

//  robotMove(pwmX, pwmY, -pwmW, 0, maxPWM);

//  Serial.print(str("#") + pwmX + str("#") + pwmY + str("#") + pwmW + str("#") + maxPWM + str("#"));
  Serial.print(str("#") + yL + str("#") + xL + str("#") + xR + str("#") + yR + str("#"));
//  for (int i = 15; i >= 0; i--) {
//    Serial.print(bitRead(dataTombol, i)); // Tampilkan bit ke-i dari data
//  } 
  Serial.print(dataTombol);
  Serial.println("#$");

//  Serial2.print(str("#") + pwmX + str("#") + pwmY + str("#") + pwmW + str("#") + maxPWM + str("#"));
  Serial2.print(str("#") + yL + str("#") + xL + str("#") + xR + str("#") + yR + str("#"));
//  for (int i = 15; i >= 0; i--) {
//    Serial2.print(bitRead(dataTombol, i)); // Tampilkan bit ke-i dari data
//  } 
  Serial2.print(dataTombol);
  Serial2.println("#$");

  joyConnect = Ps3.isConnected();
  if (joyConnect && !setMode) { 
    dataTombol = L2<<15 | L1<<14 | R2<<13 | R1<<12 | up<<11 | dw<<10 | lf<<9 | rg<<8 | T<<7 | X<<6 | S<<5 | C<<4 | SELECT<<3 | START<<2 | L3<<1 | R3;    
    ledON;
  } else {
    xL=0; yL=0; xR=0; yR=0;
    X=0; S=0; T=0; C=0;
    up=0; dw=0; lf=0; rg=0;
    L1=0; L2=0; L3=0; R1=0; R2=0; R3=0; AL2=0; AR2=0;
    SELECT=0; START=0;   
    BATT=0; 
    pwmX=0; pwmY=0; pwmW=0; maxPWM=0;
    ledOFF;
  }  

  delay(10);
}
