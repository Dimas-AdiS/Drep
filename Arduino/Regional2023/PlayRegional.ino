void runRegional1(){
  while(1){
    bacaJoystick();
  }
}


int speedDribble = 0;
void runRegional(){
  while(!O) {} delay(100);
  lcd.clear(); 
  unsigned long previousMillis = 0;
  bool setMode = 0, changeValue = 0, modeKinematics = 0;
  uint8_t setValue[2];
  SPEED = 0;
  SPEEDR = 0;

  int targetX = 0, targetY = 0, targetT = 0;

  enableMotor; 

  while(1){
    bacaJoystick(); 

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
    cursor(1,1); print("ROTASI : "); print(str(EE.SPEEDR[modeSpeed])); print(" Plan:");  print(plan); print("   ");
    cursor(1,2); print(jarX); print(" "); print(jarY); print(" "); print(Theta); print(" "); print(speedDribble); print("   "); 

    // cursor(1,3); print(jarX); print(" "); print(jarY); print(" "); print(Theta);  print("   "); 

    if(L1){
      dribble(-255); delay(300);
      dribble(0);
    }
    if(R1){
      dribble(speedDribble);  
    }

    speedDribble = map(yR, -128, 128, -255, 255);

    if(modeKinematics==0){
      // dribble(0);
      cursor(1,3); print(pwmX); print(" "); print(pwmY); print(" "); print(pwmW); print(" "); print(int(maxPWM)); print("   "); 
      // cursor(1,3); lcd.print(L2); lcd.print(L1); lcd.print(R2); lcd.print(R1); lcd.print(up); lcd.print(dw); lcd.print(lf); lcd.print(rg);
      // lcd.print(jT); lcd.print(jX); lcd.print(jS); lcd.print(jC); lcd.print(SELECT); lcd.print(START); lcd.print(L3); lcd.print(R3); 
    } else{

      if(up && btF[0] == 0){btF[0] = 1; plan++; delay(300); if(plan>maxPlan){plan=maxPlan;} SPEED = 0;}
      else if(!up && btF[0] == 1){btF[0] = 0; }
      if(dw && btF[1] == 0){btF[1] = 1; plan--; delay(300); if(plan<0){plan=0;} SPEED = 0;}
      else if(!dw && btF[1] == 1){btF[1] = 0; }

      if(lf){plan=0;} 

      parseBola(); 
      bolaCermin(); 
      bolaWide();

      if(enableRobot == ros){
        titikTujuROS(0);
        planROS(0);
        // titikTujuROS(1);
        // planROS(1);
      }

      if(enableRobot == ero){
        titikTujuERO(0);
        planERO(0);
        // titikTujuERO(1);
        // planERO(1);
      }
      
      targetX = xTargetPlan[indexPos];
      targetY = yTargetPlan[indexPos];
      targetT = tTargetPlan[indexPos];

      cursor(1,3); print(targetX); print(" "); print(targetY); print(" "); print(targetT); print("   "); 
    }
    
    // if(!O){
    //   enableMotor;
    // }

    if(R2==1){modeSpeed=2;}
    else if(L2==1){modeSpeed=0;}
    else {modeSpeed=1;} 

    if(!P){
      plan = 0; 
      jarX = 0; jarY = 0; countEncoder1 = 0; countEncoder2 = 0; countEncoder3 = 0; clear();
      kirimKeGyro(0); 
    }

    if(!D || L3){
      plan = 0; 
      targetX = homeROS[0]; targetY = homeROS[1]; targetT = homeROS[2];
      jarX = targetX; jarY = targetY; countEncoder1 = 0; countEncoder2 = 0; countEncoder3 = 0; clear();
      kirimKeGyro(targetT);
    }
    
    if(!M || R3){
      plan = 0;
      if(enableRobot == ros){
        targetX = homeROS[0]; targetY = homeROS[1]; targetT = homeROS[2];
      } else{
        targetX = homeERO[0]; targetY = homeERO[1]; targetT = homeERO[2];
      }
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