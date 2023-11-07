typedef String str; 

#define MAXPWM 255
#define MINPWM 30

#define addEE 0

bool setMode = 0;

byte setValue[2];

//joystick variable 
int xL=0, yL=0, xR=0, yR=0;
bool X=0,S=0,T=0,C=0;
bool up=0,dw=0,lf=0,rg=0;
bool L1=0,L2=0,L3=0,R1=0,R2=0,R3=0;
int AL2=0,AR2=0;
bool SELECT=0, START=0;   
uint8_t BATT=0;   

uint16_t dataTombol = 0;

byte SPEED = 0, SPEEDR;
int pwmX, pwmY, pwmW;
float maxPWM=100;

float pLF=0;
float pRF=0;
float pLR=0;
float pRR=0;

struct valEE {   
  uint8_t SPEED[3] = {70, 180, 255};
  uint8_t SPEEDR[3] = {70, 180, 255};  
}; valEE EE; 

byte modeSpeed = 1;

bool joyConnect = 0;
bool changeValue = 0;

unsigned long previousMillis = 0, previousMillis1 = 0; 

#define maxModeSpeed 3
String tampilModeSpeed[maxModeSpeed] = {
  "SLOW   : ",
  "NORMAL : ",
  "FAST   : ",
};
