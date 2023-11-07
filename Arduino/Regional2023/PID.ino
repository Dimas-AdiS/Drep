float IoutY = 0;

bool PIDBolaC(int SPX, int SPY, int SPT, int jagaBola, int maxPWM) {
  float KPX = 0.5, KDX = 3;
  float KPY = 2.7, KIY = 0.05, KDY = 10;
  float KPT = 1.2, KDT = 2.2;
  float KPTheta = 1.7;
  int outputX, outputY, outputT;
  float kpCX = 1.4, kpCY = 2.9, kpCT = 1.4;
  float kiCX = 0.01, kiCY = 0.01, kiCT = 0.016;
  float kdCX = 4.5, kdCY = 1.5, kdCT = 5.2;
  int maxSpd = 95;

  // bolaCermin();

  if (detekBolaC > 0) {
    errorXB = xBolaC;
    errorYB = yBolaC - SPY;
    errorTB = -tBolaC;

    if (jagaBola == 1 && yBolaC > 70) {
      KPX *= 10;
      KDX *= 10;
    }

    if (rBolaC > 160) {
      KPT *= 1.2;
      // KPX*=1.5;
      KPY *= 2;
      KDY *= 2;
    }

    if (errorYB < 20 && errorYB > -20) {
      IoutY += KIY * errorYB;
      IoutY = constrain(IoutY, -maxPWM, maxPWM);
    } else if ((errorYB > 0 && IoutY < 0) || (errorYB < 0 && IoutY > 0)) {
      IoutY = 0;
    } else {
      IoutY = 0;
    }

    float outputPIDX = (KPX * errorXB) + (KDX * (errorXB - errorXB1));
    float outputPIDY = IoutY + (KPY * errorYB) + (KDY * (errorYB - errorYB1));
    float outputPIDT = (KPT * errorTB) + (KDT * (errorTB - errorTB1));

    errorT = tBolaC;
    iT += errorT;

    float PIDTBolaC = (kpCT * errorT) + (kiCT * iT) + (kdCT * (errorT - errorT1));
    int spdT = constrain(PIDTBolaC, -maxSpd, maxSpd);
    errorT1 = errorT;

    outputX = constrain(outputPIDX, -maxPWM, maxPWM);
    outputY = constrain(outputPIDY, -maxPWM, maxPWM);
    outputT = constrain(outputPIDT, -maxPWM, maxPWM);

    float thetaNow = Theta - SPT;

    if (thetaNow > 180) {
      thetaNow -= 360;
    } else if (thetaNow < -180) {
      thetaNow += 360;
    }

    rTheta = thetaNow * KPTheta;

    if (jagaBola == 1 && yBolaC >= 30) {
      moveRobot(outputX, 0, 0, maxPWM);
    } else if (rBolaC < SPY + 50 && jagaBola == 0) {
      moveRobot(outputX + rTheta, outputY, -outputT, maxPWM);
    } else if ((tBolaC > 90 || tBolaC < -90) && jagaBola == 0) {
      moveRobot(0, 0, spdT, maxPWM);
    } else {
      moveRobot(outputX, outputY, -outputT, maxPWM);
    }

    errorXB1 = errorXB;
    errorYB1 = errorYB;
    errorTB1 = errorTB;

  } else {
    pwmMotor(0, 0, 0, 0);
  }

  // Serial.println(jagaBola);
  if (jarD == 0) {
    titikTuju = 1;
  } else {
    titikTuju = 0;
  }

  return titikTuju;
}

long int countDetekRobot = 0;
bool enableInitCount = 0;
bool PIDRobot(int maxPWM, int countDetek) {
  float KP = 2.3, KI = 0.05, KD = 11;
  int output;

  if (detekBolaB > 0) {
    errorT = -tBolaB;

    float outputPID = (KP * errorT) + (KD * (errorT - errorT1));

    errorT1 = errorT;

    output = constrain(outputPID, -maxPWM, maxPWM);

    moveRobot(0, 0, output, maxPWM);

    if(enableInitCount==1){
      countDetekRobot = millis();
      enableInitCount = 0;
    }

    if (errorT < 5 && errorT > -5 && ((millis() - countDetekRobot)/100) >= countDetek) { 
      titikTuju = 1;
      enableInitCount = 1;
    } else {
      titikTuju = 0;
    }

  } else {
    stop();
    titikTuju = 0;
  }
  return titikTuju;
}

bool putarKeArah(int targetX, int targetY, int maxPWM) {
  float x, y, r, target, sudutTuju;
  float KPT = 1.7, KIT = 0.3, KDT = 2;
  int outputT = 0;

  x = (targetX - jarX) / 100;
  y = (targetY - jarY) / 100;

  r = sqrt((x * x) + (y * y));
  sudutTuju = 0;

  if (x > 0) {
    sudutTuju = 90 - ((asin(y / r)) * (180 / PI));
  } else {
    sudutTuju = (asin((y / r)) * (180 / PI)) - 90;
  }

  int errorT = Theta - sudutTuju;

  errorT1 = errorT;

  float outputPIDT = (KPT * errorT) + (KDT * (errorT - errorT1));

  outputT = constrain(outputPIDT, -maxPWM, maxPWM);

  if ((errorT < 5 && errorT > -5)) {
    titikTuju = 0;
    if (errorT > 0) {
      moveRobot(10, 0, -outputT, maxPWM);
    } else {
      moveRobot(-10, 0, -outputT, maxPWM);
    }
  } else {
    titikTuju = 1;
    moveRobot(0, 0, -outputT, maxPWM);
  }

  return titikTuju;
}

bool enMotor = 1;
bool jagaBola = 0;
int jarakJ = 100;
int derJ = 0;
int spX = 0;
void cobaPIDBolaC() {
  int enablePID = 0;
  bool manualMode = 0;
  byte statusDribble = 0;
  lcd.clear();
  while (1) {

    if (manualMode) {
      cursor(1, 0);
      print("SPEED ");
      print(tampilModeSpeed[modeSpeed]);
      print(EE.SPEED[modeSpeed]);
      print("   ");
      cursor(1, 1);
      print("ROTASI : ");
      print(EE.SPEEDR[modeSpeed]);
      print(" D:");
      print(statusDribble);
      print("   ");
      cursor(1, 2);
      print(pwmX);
      print(" ");
      print(pwmY);
      print(" ");
      print(pwmW);
      print(" ");
      print(maxPWM);
      print("  ");
      cursor(1, 3);
      print(L2);
      print(L1);
      print(R2);
      print(R1);
      print(up);
      print(dw);
      print(lf);
      print(rg);
      print(jT);
      print(jX);
      print(jS);
      print(jC);
      print(SELECT);
      print(START);
      print(L3);
      print(R3);
    } else {
      cursor(0, 0);
      lcd.write(0b11110010);
      print(Theta);
      print(" ");
      print("x");
      print(jarX);
      print(" ");
      print(jarY);
      print(" ");
      print(enablePID);
      print("  ");
      cursor(0, 1);
      print("X");
      print(xBolaC);
      print(" Y");
      print(yBolaC);
      print(" T");
      print(tBolaC);
      print(" D:");
      print(statusDribble);
      print("  ");
      cursor(0, 2);
      print("R");
      print(rBolaC);
      print(" ");
      print(rTheta);
      print(" J:");
      print(jagaBola);
      print(" ");
      print(" M:");
      print(manualMode);
      print("  ");
      cursor(0, 3);
      print("J");
      print(jarakJ);
      print(" T");
      print(derJ);
      print(" X");
      print(spX);
      print("  ");
    }

    parseBola();
    bolaCermin();

    bacaJoystick();

    if (!O) {
      pwmMotor(0, 0, 0, 0);
      dribble(-255);
      delay(1000);
      dribble(0);
    }

    if (jC && btF[0] == 0) {
      btF[0] = 1;
      enablePID = !enablePID;
      manualMode = 0;
      jagaBola = 0;
    } else if (!jC) {
      btF[0] = 0;
    }

    if (jS && btF[1] == 0) {
      btF[1] = 1;
      jagaBola = !jagaBola;
      manualMode = 0;
      enablePID = 0;
    } else if (!jS) {
      btF[1] = 0;
    }
    if (jT && btF[2] == 0) {
      btF[2] = 1;
      manualMode = !manualMode;
      jagaBola = 0;
      enablePID = 0;
    } else if (!jT) {
      btF[2] = 0;
    }

    if (jX && btF[3] == 0) {
      enMotor = !enMotor;
      btF[3] = 1;
    } else if (!jX) {
      btF[3] = 0;
    }

    if (R1 && btF[4] == 1) {
      btF[4] = 0;
      statusDribble = 1;
    } else if (L1 && btF[4] == 1) {
      btF[4] = 0;
      statusDribble = 2;
    } else if (!R1 || !L1) {
      btF[4] = 1;
    }

    if (R3) {
      statusDribble = 0;
    }

    if (statusDribble == 1) {
      dribble(200);
    } else if (statusDribble == 2) {
      dribble(-200);
    } else {
      dribble(0);
    }

    if (enMotor) {
      enableMotor;
    } else {
      disableMotor;
    }

    if (SELECT) {
      delay(200);
      pwmMotor(0, 0, 0, 0);
      break;
    }
    if (!C) {
      delay(200);
      pwmMotor(0, 0, 0, 0);
      break;
    }

    if (enablePID == 1 && jagaBola == 0) {
      PIDBolaC(0, jarakJ, derJ, 0, 180);

      if (L1) {
        spX -= 5;
        if (spX < -150) { spX = -150; }
      } else if (R1) {
        spX += 5;
        if (spX > 150) { spX = 150; }
      }

      if (up) {
        jarakJ -= 5;
        if (jarakJ < 30) { jarakJ = 30; }
      } else if (dw) {
        jarakJ += 5;
        if (jarakJ > 200) { jarakJ = 200; }
      }

      if (lf) {
        derJ += 5;
        if (derJ > 180) { derJ = 180; }
      } else if (rg) {
        derJ -= 5;
        if (derJ < -180) { derJ = -180; }
      }


    } else if (jagaBola == 1) {
      PIDBolaC(0, yBolaC, Theta, 1, 180);
    } else if (manualMode) {
      manualMode1();
      // dribble(0);
    } else {
      // dribble(0);
      stop();
    }
  }
  dribble(-255);
  delay(1000);
  dribble(0);
  clear();
}
