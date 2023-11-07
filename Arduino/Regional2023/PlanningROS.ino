void planROS(int strategi){
  if(strategi==0){

    if(plan == 0){
      indexPos = 0;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 1){
      dribble(100);
      indexPos = 1;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 2){  
      if(PIDBolaC(0, yBolaC, Theta, 0, 120)){plan++;}
      if(yBolaC>0 && yBolaC<140){countBolaDekat++;}
      else{countBolaDekat=0;}
      if(countBolaDekat>5){plan++;}  
    } else if(plan == 3){ 
      if(PIDBolaC(0, yBolaC, Theta, 1, 120)){plan++;}  
      if(yBolaC<120){countBolaDekat++;}
      else{countBolaDekat=0;}
      if(countBolaDekat>2){plan++;}  
    } else if(plan == 4){ 
      if(PIDBolaC(0,30,Theta,0,120)){plan++;}
    } else if(plan == 5){
      indexPos = 2;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 6){
      dribble(200);
      if(PIDRobot(60,10)){plan++;}
    } else if(plan == 7){
      stop(); 
      dribble(-20);  
      tendangSlow();
      plan++;
    } else if(plan == 8){
      indexPos = 3;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 9){ 
      dribble(200);
      if(PIDBolaC(0, yBolaC, Theta, 0, 120)){plan++;}
      if(yBolaC>0 && yBolaC<150){countBolaDekat++;}
      else{countBolaDekat=0;}
      if(countBolaDekat>5){plan++;}   
    } else if(plan == 10){ 
      if(PIDBolaC(0, yBolaC, Theta, 1, 120)){plan++;}  
      if(yBolaC<110){countBolaDekat++;}
      else{countBolaDekat=0;}
      if(countBolaDekat>1){plan++;}    
    } else if(plan == 11){ 
      if(PIDBolaC(0,30,Theta,0,120)){plan++;}
    } else if(plan == 12){ 
      moveRobot(0,0,40,40); delay(600);
      stop(); delay(200);
      dribble(10); 
      tendangSlow();
      // tendangFull();
      plan++;
    } else{
      dribble(20);
      stop();
    }
  }
}
 