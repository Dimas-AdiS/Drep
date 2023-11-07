typedef String str; 

#define uus 1
#define ero 2
#define ros 3

uint8_t enableRobot = 0;

#define addEE 0

#define MAXPWM 255
#define MINPWM 20

int pwmM4_1 = -1;
int pwmM4_2 = -1;

int homeROS[3] = {30, 250, 90};
int homeERO[3] = {550, 250, -90};

struct varEEPROM {
  uint8_t enableRobot = 0;
  bool enableTEAM = 0;
  uint8_t SPEED[3] = {70, 180, 255};
  uint8_t SPEEDR[3] = {70, 180, 255};  
  int EEjarX, EEjarY;

}; varEEPROM EE;

//joystick variable 
int16_t xL=0, yL=0, xR=0, yR=0;
bool jX=0,jS=0,jT=0,jC=0;
bool up=0,dw=0,lf=0,rg=0;
bool L1=0,L2=0,L3=0,R1=0,R2=0,R3=0;
uint8_t AL2=0,AR2=0;
bool SELECT=0, START=0;   
uint8_t BATT=0;  

uint8_t millisInterrupt = 50;
uint8_t convertInterrupt = 1000/millisInterrupt;
long int detikMain = 0, countInterrupt = 0, countMs = 0; 

long int countTendang = 0;

bool parsing = false;
String sData, data[30];

int derM1, derM2, derM3, derM4;
float vM1,vM2,vM3,vM4;

float dRoda = 6.5;

float offsetGyro = 0.0;
float dataGyro, Theta, rTheta;

int rCermin = 300, wCermin = 800, hCermin = 600, cXCermin = 400, cYCermin = 300;
int wWide= 800, hWide= 448, cXWide= 400, cYWide = 448;

bool titikTuju=0, kejarBola=0, kejarBola1=0, detekBolaC=0, detekBolaB = 0, dapatBola = 0, dapatBola1 = 0;
float xBola=-1, yBola=-1, xBola1=-1, yBola1=-1, adaRobot, xBolaB, yBolaB, rBolaB, tBolaB, 
      xBolaC,yBolaC,rBolaC,rBolaC1,tBolaC,xBolaBL,yBolaBL;

float error1R = 0, errorXB = 0, errorYB = 0, errorTB, errorTT, errorXB1 = 0, errorYB1 = 0, errorTB1 = 0, errorTT1 = 0;

float errorX, errorY, errorT, errorX1, errorY1, errorT1, SPEED = 0, SPEEDR = 0;
float iX, iY, iT;
float vX, vY, vT;
int xTarget, yTarget, tTarget;
int strategi = 0;

float perRotasi; //jumlah pulsa 1 rotasi encoder
float kelRoda; //keliling roda omni rotary
float jarPerPulsa; //jarak per pulsa omni encoder
float jar1, jar2, jar3, jarX, jarY;

int pwmX, pwmY, pwmW;
float maxPWM=100;
float maxx = 0; 

int indexPos = 0;
int plan=0;

int maxPlan = 0;

long int countEncoder1, countEncoder2, countEncoder3, freqEncoder1, freqEncoder2, freqEncoder3, countGaDetekC, countDetek; 

int8_t sellectMenu = 0, subMenu = 0;

String inString = "";

char intruksiPlay = 'S', intruksiFull = 'K', enableInisial = 'N';

int8_t scrollScreen = 0;  

int xTargetPlan[20], yTargetPlan[20], tTargetPlan[20];

int countBolaDekat = 0;

bool btF[20];

int arahGerakX = 0, arahGerakY = 0;

float speedAksel = 20;
int8_t modeSpeed = 1;

const int8_t maxTampilStart = 8;
const char *tampilStart[maxTampilStart] = {
  "AutoC",
  "AutoM", 
  "Robot",
  "Kick S",
  "Kick F", 
  "PID C ", 
  "PID B ", 
  "Manual",
};

#define subMenuAUTOC 0
#define subMenuAUTOM 1
#define subMenuROBOT 2
#define subMenuKICKS 3
#define subMenuKICKF 4
#define subMenuPIDC 5
#define subMenuPIDB 6
#define subMenuMANUAL 7

const char *tampilRobot[10] = {
  " ",
  " UUS ",
  " ERO ",
  " ROS "
};

#define maxModeSpeed 3
String tampilModeSpeed[maxModeSpeed] = {
  "S : ",
  "N : ",
  "F : ",
};