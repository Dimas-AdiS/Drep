void bacaJoystick1(){
  char getData = SerialJoystick.read();
  if (getData == 'x') {
    xL = SerialJoystick.parseInt(); //X Joystick Kiri
    
    Serial.println(xL);    
    // Serial.println(xL);
    // if (SerialJoystick.read() == 'y') {
    //   yL = SerialJoystick.parseInt(); //Y Joystick Kiri
    //   if (SerialJoystick.read() == 'X') {
    //     xR = SerialJoystick.parseInt(); //X Joystick Kanan
    //     if (SerialJoystick.read() == 'Y') {
    //       yR = SerialJoystick.parseInt(); //Y Joystick Kanan
    //       if (SerialJoystick.read() == 'B') {
    //         int dataJoystick = SerialJoystick.parseInt(); //Button Joystik
    //         Serial.println(dataJoystick);

    //         L2 = dataJoystick>>15 & 1;
    //         L1 = dataJoystick>>14 & 1;
    //         R2 = dataJoystick>>13 & 1;
    //         R1 = dataJoystick>>12 & 1;
    //         up = dataJoystick>>11 & 1;
    //         dw = dataJoystick>>10 & 1;
    //         lf = dataJoystick>>9 & 1;
    //         rg = dataJoystick>>8 & 1;
    //         jT = dataJoystick>>7 & 1;
    //         jX = dataJoystick>>6 & 1;
    //         jS = dataJoystick>>5 & 1;
    //         jC = dataJoystick>>4 & 1;
    //         SELECT = dataJoystick>>3 & 1;
    //         START = dataJoystick>>2 & 1;
    //         L3 = dataJoystick>>1 & 1;
    //         R3 = dataJoystick & 1;
    //       }
    //     }
    //   }
    // }
  }
}

void bacaJoystick(){
  SerialJoystick.write('*'); 
  delay(2);
  xL=0; yL=0; xR=0; yR=0;
  jX=0; jS=0; jT=0; jC=0;
  up=0; dw=0; lf=0; rg=0;
  L1=0; L2=0; L3=0; R1=0; R2=0; R3=0;
  SELECT=0; START=0;   
  while (SerialJoystick.available()) {
    char inChar = SerialJoystick.read(); 
    sData += inChar;
    if (inChar == '$') {
      parsing = true;
    }
    if (parsing) {
      // Serial.println(sData);
      int q = 0;
      for (int i = 0; i < sData.length(); i++) {
        if (sData[i] == '#') {
          q++;
          data[q] = "";
        } else {
          data[q] += sData[i];
        }
      }

      xL = data[1].toInt();
      yL = data[2].toInt(); 
      xR = data[3].toInt();
      yR = data[4].toInt();
      int dataJoystick = data[5].toInt();

      L2 = dataJoystick>>15 & 1;
      L1 = dataJoystick>>14 & 1;
      R2 = dataJoystick>>13 & 1;
      R1 = dataJoystick>>12 & 1;
      up = dataJoystick>>11 & 1;
      dw = dataJoystick>>10 & 1;
      lf = dataJoystick>>9 & 1;
      rg = dataJoystick>>8 & 1;
      jT = dataJoystick>>7 & 1;
      jX = dataJoystick>>6 & 1;
      jS = dataJoystick>>5 & 1;
      jC = dataJoystick>>4 & 1;
      SELECT = dataJoystick>>3 & 1;
      START = dataJoystick>>2 & 1;
      L3 = dataJoystick>>1 & 1;
      R3 = dataJoystick & 1;
       
      parsing = false;
      sData = "";
    }
  }  
  
}

void manualMode(){
  while(!O) {} delay(100);
  lcd.clear(); 

  int plan=0;
  unsigned long previousMillis = 0;
  bool setMode = 0, changeValue = 0, modeKinematics = 0;
  uint8_t modeSpeed = 1, setValue[2];
  SPEED = 0;
  SPEEDR = 0;

  int targetX = 0, targetY = 0, targetT = 0;

  enableMotor;

  while(1){
    bacaJoystick();
    // if(!O){setMode = !setMode; delay(300);}  

    if(START){setMode = 0;}    
    if(SELECT){setMode = 1;}

    if(jC){modeKinematics = 1; clear();} 
    if(jX){modeKinematics = 0; clear();}    

    if(setMode){
      cursor(0,0); print(">");
    } else {
      cursor(0,0); print(" ");
    }

    cursor(1,0); print("SPEED "); print(tampilModeSpeed[modeSpeed]); print(str(EE.SPEED[modeSpeed])); print(" M:");  print(modeKinematics); print("   ");
    cursor(1,1); print("ROTASI : "); print(str(EE.SPEEDR[modeSpeed]));  print("   ");

    // cursor(1,3); print(jarX); print(" "); print(jarY); print(" "); print(Theta);  print("   "); 

    
    if(modeKinematics==0){
      cursor(1,2); print(pwmX); print(" "); print(pwmY); print(" "); print(pwmW); print(" "); print(int(maxPWM)); print("   "); 
    } else{
      if(R1){plan++; delay(300); if(plan>3){plan=3;} SPEED = 0;}
      if(L1){plan--; delay(300); if(plan<0){plan=0;} SPEED = 0;}
      
      targetX = xTargetPlan[plan]; targetY = yTargetPlan[plan]; targetT = tTargetPlan[plan]; 


      // if(up){
      //   targetX = 0; targetY = 150; targetT = 0; SPEED = 0;
      // }
      // if(rg){
      //   targetX = 150; targetY = 150; targetT = 0; SPEED = 0;
      // }
      // if(lf){
      //   targetX = -150; targetY = 150; targetT = 0; SPEED = 0;
      // }
      // if(dw){
      //   targetX = 0; targetY = 0; targetT = 0; SPEED = 0;
      // }

      runKinematics(targetX, targetY, targetT, EE.SPEED[modeSpeed]);
      cursor(1,2); print(targetX); print(" "); print(targetY); print(" "); print(targetT); print("   "); 
    }
    cursor(1,3); lcd.print(L2); lcd.print(L1); lcd.print(R2); lcd.print(R1); lcd.print(up); lcd.print(dw); lcd.print(lf); lcd.print(rg);
    lcd.print(jT); lcd.print(jX); lcd.print(jS); lcd.print(jC); lcd.print(SELECT); lcd.print(START); lcd.print(L3); lcd.print(R3); 

    if(R2==1){modeSpeed=2;}
    else if(L2==1){modeSpeed=0;}
    else {modeSpeed=1;} 

    if(!M || R3){
      targetX = xTargetPlan[0]; targetY = yTargetPlan[0]; targetT = tTargetPlan[0];
      jarX = targetX; jarY = targetY; countEncoder1 = 0; countEncoder2 = 0; countEncoder3 = 0; clear();
      kirimKeGyro(targetT);
    }

    if(setMode){
      setValue[0] = EE.SPEED[modeSpeed];
      setValue[1] = EE.SPEEDR[modeSpeed]; 
  
      if(up){
        changeValue = 1;
        setValue[0]++;
      }
      if(dw){
        changeValue = 1;
        setValue[0]--;
      }

      if(rg){
        changeValue = 1;
        setValue[1]++;
      }
      if(lf){
        changeValue = 1;
        setValue[1]--;
      }
    }

    if(changeValue == 1){
      changeValue = 0;
      EE.SPEED[modeSpeed] = setValue[0];
      EE.SPEEDR[modeSpeed] = setValue[1];  
      
      EEPROM.put(addEE, EE);  

      delay(2);
    } 
    
    if(modeKinematics == 0){
      yL = constrain(yL,-127,127);
      xL = constrain(xL,-127,127);
      yR = constrain(yR,-127,127);
      xR = constrain(xR,-127,127); 
      
      SPEED = EE.SPEED[modeSpeed];
      SPEEDR = EE.SPEEDR[modeSpeed];

      pwmY = map(yL,-127, 127, -SPEED, SPEED);
      pwmX = map(xL,-127, 127, -SPEED, SPEED); 
      pwmW = map(xR,-127, 127, -SPEEDR, SPEEDR);  

      // if(!setMode){  
      //   if(up){
      //     pwmY = SPEED;
      //   }
      //   if(dw){
      //     pwmY = -SPEED;
      //   }
      //   if(rg){
      //     pwmX = SPEED;
      //   }
      //   if(lf){
      //     pwmX = -SPEED;
      //   }
      // }
      
      
      if(SPEED > SPEEDR){
        maxPWM = SPEED;
      } else {
        maxPWM = SPEEDR;
      }
      
      maxPWM = constrain(maxPWM, MINPWM, MAXPWM); 
      moveRobot(pwmX,pwmY,pwmW,maxPWM);
    } else{

    }

    if(!C){delay(200); disableMotor; clear(); break;}
  }

}

void manualMode1(){  
    // bacaJoystick();   
 
    if(R2==1){modeSpeed=2;}
    else if(L2==1){modeSpeed=0;}
    else {modeSpeed=1;}  
     
    yL = constrain(yL,-127,127);
    xL = constrain(xL,-127,127);
    yR = constrain(yR,-127,127);
    xR = constrain(xR,-127,127); 
    
    SPEED = EE.SPEED[modeSpeed];
    SPEEDR = EE.SPEEDR[modeSpeed];

    pwmY = map(yL,-127, 127, -SPEED, SPEED);
    pwmX = map(xL,-127, 127, -SPEED, SPEED); 
    pwmW = map(xR,-127, 127, -SPEEDR, SPEEDR);       
    
    if(SPEED > SPEEDR){
      maxPWM = SPEED;
    } else {
      maxPWM = SPEEDR;
    }
    
    maxPWM = constrain(maxPWM, MINPWM, MAXPWM); 
    moveRobot(pwmX,pwmY,pwmW,maxPWM);  
}
