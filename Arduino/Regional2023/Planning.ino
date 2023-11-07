void moveToKoordinat(int x, int y, int t, int maxPWM){
  titikTuju = 0;
  clear();
  while(titikTuju == 0){
    bacaJoystick();
    runKinematics(x, y, t, maxPWM);

    cursor(0,2); 
    print("X"); print(jarX); print(" Y"); print(jarY); print(" T"); print(Theta);  print("  "); 
    cursor(0,3); 
    print("X"); print(xTarget); print(" Y"); print(yTarget); print(" T"); print(tTarget);  print("  "); 

    if(jX){
      stop();
      break;
    }
  }
}
 