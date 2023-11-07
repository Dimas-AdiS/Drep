void updateJarak() {
  float vX, vY;

  vX = ((2*jar3) - jar2 - jar1 )/3.0;   
  vY = ( (jar2 * sqrt(3) - (jar1 * sqrt(3))) )/3.0;     
   
  parseGyro();  
  if (dataGyro < 0) {
    Theta = 360 + dataGyro;
  } else {
    Theta = dataGyro;
  }

  if (Theta > 180) {
    Theta -= 360;
  } 
  else if (Theta < -180) {
    Theta += 360;
  }
  
  jarX += (cos(radians(Theta-offsetGyro)) * vX + sin(radians(Theta-offsetGyro)) * vY);
  jarY += (-sin(radians(Theta-offsetGyro)) * vX + cos(radians(Theta-offsetGyro)) * vY);
  // jarX = (cos(radians(Theta-offsetGyro)) * vX + sin(radians(Theta-offsetGyro)) * vY);
  // jarY = (-sin(radians(Theta-offsetGyro)) * vX + cos(radians(Theta-offsetGyro)) * vY);

  // if(vX != 0 || vY!=0){
  //   // Serial.println(vX +str(" ") + vY);
  //   Serial.println(jar1 + str(" ") + jar2 + str(" ") + jar3);
  // }
  
}

void moveRobotKinematics(int X, int Y, int W, int maxPWM) {
//  float vM=0,L,R,B,tL,tR,tB;
  float  v1, v2, v3, v4, tV1, tV2, tV3, tV4;
  float speedAksel = 4;
 
  maxx = maxPWM; 


  vM1 = (sin(radians(derM1-Theta)) * X) - (cos(radians(derM1-Theta)) * Y) + (W);
  vM2 = (sin(radians(derM2-Theta)) * X) - (cos(radians(derM2-Theta)) * Y) + (W);
  vM3 = (sin(radians(derM3-Theta)) * X) - (cos(radians(derM3-Theta)) * Y) + (W);
  vM4 = (sin(radians(derM4-Theta)) * X) - (cos(radians(derM4-Theta)) * Y) + (W);
   
  v1 = abs(vM1);
  v2 = abs(vM2);
  v3 = abs(vM3);
  v4 = abs(vM4);

  if(vM1>0){tV1=1;} else{tV1=-1;}
  if(vM2>0){tV2=1;} else{tV2=-1;}
  if(vM3>0){tV3=1;} else{tV3=-1;}
  if(vM4>0){tV4=1;} else{tV4=-1;}

  if(v1>v2 && v1>v3 && v1>v4 && v1>maxx){ 
    vM1 = tV1*maxx;
    vM2 = tV2*maxx*(v2/v1);
    vM3 = tV3*maxx*(v3/v1);
    vM4 = tV4*maxx*(v4/v1);
  }

  if(v2>v1 && v2>v3 && v2>v4 && v2>maxx){  
    vM1 = tV1*maxx*(v1/v2);
    vM2 = tV2*maxx;
    vM3 = tV3*maxx*(v3/v2);
    vM4 = tV4*maxx*(v4/v2);
  }

  if(v3>v1 && v3>v2 && v3>v4 && v3>maxx){  
    vM1 = tV1*maxx*(v1/v3);
    vM2 = tV2*maxx*(v2/v3);
    vM3 = tV3*maxx;
    vM4 = tV4*maxx*(v4/v3);
  }

  if(v4>v1 && v4>v2 && v4>v3 && v4>maxx){  
    vM1 = tV1*maxx*(v1/v4);
    vM2 = tV2*maxx*(v2/v4);
    vM3 = tV3*maxx*(v3/v4);
    vM4 = tV4*maxx;
  }

  pwmMotor(vM1, vM2, vM3, vM4);
  
  arahGerakX = X;
  arahGerakY = Y;
}

bool runKinematics(int x, int y, int t, int maxPWM){
  float kpXY = 3.3, kiXY = 0.025, kdXY = 0;
  float kpT = 5.1, kiT = 0.155, kdT = 0, maxRPM = maxPWM;
  float eTheta, pTheta,mTheta, batasPlus, batasMin;
  bool titikTuju = 0;

  errorX = x - jarX;
  errorY = y - jarY;

  if(Theta < 0){pTheta = 360 + Theta;}
  else{pTheta = Theta;}
  mTheta = Theta;  
  
  if(t<0){ eTheta = 360 + t; }
  else{ eTheta = t; }

  if(pTheta > eTheta){errorT = pTheta - eTheta;}
  else {errorT = Theta - t;}
   
  if(errorT>180){errorT = (int) (errorT - 360);}
 
  long r = sqrt(((errorX / 10) * (errorX / 10)) + ((errorY / 10) * (errorY / 10)));
  r *= 10;

  if (r < 20) {
    iX += errorX;
    iY += errorY;
    if (errorT < 15 && errorT > -15) { iT += errorT; }
  }else{
    iX=iY=iT=0;
  }

  vX = errorX * kpXY + (iX * kiXY);
  vY = errorY * kpXY + (iY * kiXY);
  vT = (errorT * kpT) + (iT * kiT);  
  
  if ((errorX < 15 && errorX > -15) && (errorY < 15 && errorY > -15) && (errorT < 5 && errorT > -5)) { 
    titikTuju = 1; SPEED = maxPWM;
  }
  else {
    titikTuju = 0;
    if (SPEED < maxPWM) {
      SPEED += speedAksel;
    } else {
      SPEED = maxPWM;
    }
  } 
  
  moveRobotKinematics(vX, vY, -vT , SPEED); 
  // moveRobot(vX, vY, -vT , SPEED); 

  return titikTuju;
}
 