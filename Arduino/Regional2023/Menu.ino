
byte tampilSub = 0;
void menuAwal(){
  parseBola();
  bolaCermin();
  bolaWide();
  listenCoach();
  updateToCoach();

  if(!O && sellectMenu == 0 && subMenu == subMenuAUTOC){ 
    runRegional();  
  }
  if(!O && sellectMenu == 0 && subMenu == subMenuMANUAL){ 
    manualMode();  
  } 
  if(!O && sellectMenu == 0 && subMenu == subMenuKICKS){ 
    tendangSlow();  
  } 
  if(!O && sellectMenu == 0 && subMenu == subMenuKICKF){ 
    tendangFull();  
  }  
  if(!O && sellectMenu == 0 && subMenu == subMenuPIDC){ 
    cobaPIDBolaC();  
  }  
  if(!O && sellectMenu == 0 && subMenu == subMenuROBOT){ 
    enableRobot++;
    delay(200);
    if(enableRobot > 3){
      enableRobot = 1;
    }
    EE.enableRobot = enableRobot;
    EEPROM.put(addEE, EE);
  } 
 
  cursor(0, sellectMenu); print(">");

  cursor(1, 0); print(tampilStart[subMenu]);  
  print(tampilRobot[enableRobot]); print(jarD); print(" "); lcd.write(intruksiFull); 
  print(" "); lcd.write(intruksiPlay);  print("  "); // print(detikMain);
  cursor(1,1); print("J"); print(jarX); print(" "); print(jarY); print(" "); lcd.print(Theta); print("  ");
  cursor(1,2); print("x"); print(xBolaC); print(" "); print(yBolaC); print(" "); print(xBolaB); print(" ");print(yBolaB); print("  "); 

  // cursor(1,2); print("E"); print(countEncoder2); print(" "); print(countEncoder3); print(" "); print(countEncoder1); print(" "); 
  // cursor(1, 2); print(str(int(countEncoder1))); print(" "); print(str(int(countEncoder2))); print(" "); print(str(int(countEncoder3))); 

  
  // if(tampilSub == 0){
  // } else if(tampilSub == 1){
  //   cursor(1,1); print("E"); print(countEncoder2); print(" "); print(countEncoder3); print(" "); print(countEncoder1);  print(" ");
  // }

  if(!O && sellectMenu == 1){
    tampilSub++; delay(300);
    if(tampilSub>1) {tampilSub=0;}
  } 
  if(!C && sellectMenu == 1){
    jarX = 0; jarY = 0; countEncoder1 = 0; countEncoder2 = 0; countEncoder3 = 0; clear();
    kirimKeGyro(0);
  }

  if(!P && sellectMenu == 0){
    subMenu++;
    delay(200);
  }else if(!M && sellectMenu == 0){
    subMenu--;
    delay(200);
  }
  if(subMenu>maxTampilStart-1){
    subMenu = 0;
  }else if(subMenu<0){
    subMenu = maxTampilStart-1;
  }

  if(!D){
    sellectMenu++; 
    delay(200);
    clear();
  }else if(!U){ 
    sellectMenu--;
    delay(200);
    clear();
  }
  if(sellectMenu > 3){
    sellectMenu = 0; 
  }else if(sellectMenu < 0){  
    sellectMenu = 3; 
  }

  if(!C && sellectMenu==0){
    disableMotor;
  } 
  if(!O && sellectMenu==0){
    enableMotor;
  }
  
  // cursor(1,3); print(proxy1); print(proxy2); print(proxy3); print(proxy4); 
  // print(proxy5); print(proxy6); print(proxy7); print(proxy8); print(proxy9);
  
  // pwmMotor(pwmX,pwmY,pwmW,0);
  
  // lcd.setCursor(1, 0); lcd.print(tampilStart[mm]); lcd.print(" R"); lcd.write(enableRobot); lcd.print(" "); lcd.print(" T"); lcd.print((int)Theta); lcd.print(" "); lcd.print(jarD); lcd.print("  ");  
  // lcd.setCursor(1, 1); lcd.print("x"); lcd.print((int)jarX); lcd.print(" "); lcd.print((int)jarY); lcd.print("  "); //lcd.print("x"); lcd.print((int)jarX1); lcd.print(" "); lcd.print((int)jarY1); lcd.print(" "); lcd.print(jarD1); lcd.print(" ");
  // lcd.setCursor(1, 2); lcd.print("x"); lcd.print((int)xBola); lcd.print(" "); lcd.print((int)yBola); lcd.print(" X"); lcd.print((int)xBola1); lcd.print(" "); lcd.print((int)yBola1);  lcd.print("  ");
  // lcd.setCursor(1, 3); lcd.print("x"); lcd.print((int)xBolaB); lcd.print(" "); lcd.print((int)yBolaB); lcd.print(" X"); lcd.print((int)xBolaC); lcd.print(" "); lcd.print((int)yBolaC);  lcd.print("  ");
}