#include <Ps3Controller.h> 
#include <EEPROM.h>
#include "Variabel.h" 

#define ledPin 2
#define pinSetting 0

#define ledON digitalWrite(ledPin, HIGH)
#define ledOFF digitalWrite(ledPin, LOW)

//char *MAC = "78:dd:08:65:53:bb"; //UUS
//char *MAC = "40:22:d8:5f:0b:26"; //ERO
char *MAC = "78:dd:08:65:53:ba"; //ROS
//char *MAC = "ba:e7:b2:2d:22:ae"; //stikku  
// char *MAC = "82:00:23:d7:ca:49"; //xbox
 
bool btnPress = 0;

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
  
  Ps3.begin(MAC); 
  
  EEPROM.begin(1023); 
  EEPROM.get(addEE, EE); 
  
  ledON;
  delay(200);
  ledOFF;
  delay(200);
}

long int timerBlinking = 0;

void loop() {      
  joyConnect = Ps3.isConnected();
  if(joyConnect){   

    if(btnPress == 1){
      timerBlinking = millis();
      ledOFF;
      btnPress = 0;      
    } else if(millis() - timerBlinking > 50){
      ledON;        
    }
    
    dataTombol = L2<<15 | L1<<14 | R2<<13 | R1<<12 | up<<11 | dw<<10 | lf<<9 | rg<<8 | T<<7 | X<<6 | S<<5 | C<<4 | SELECT<<3 | START<<2 | L3<<1 | R3;

    if(dataTombol>0){
      btnPress = 1;
    }
//    Serial.write('x');
//    Serial.print(xL);
//    Serial.write('y');
//    Serial.print(yL);
//    Serial.write('X');
//    Serial.print(xR);
//    Serial.write('Y');
//    Serial.print(yR);
//    Serial.write('B'); 
//    Serial.println(dataTombol); 
//
//    Serial2.write('x');
//    Serial2.print(xL);
//    Serial2.write('y');
//    Serial2.print(yL);
//    Serial2.write('X');
//    Serial2.print(xR);
//    Serial2.write('Y');
//    Serial2.print(yR);
//    Serial2.write('B'); 
//    Serial2.println(dataTombol); 
    
//    Serial2.println();    

    if(Serial.read()=='*'){
      Serial.print(str("#") + xL + str("#") + yL + str("#") + xR + str("#") + yR + str("#"));
      Serial.print(dataTombol);
      Serial.println("#$"); 
   }
   if(Serial2.read()=='*'){ 
      Serial2.print(str("#") + xL + str("#") + yL + str("#") + xR + str("#") + yR + str("#"));
      Serial2.print(dataTombol);
      Serial2.println("#$");    
    }
    
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
   
//  delay(10);
}
