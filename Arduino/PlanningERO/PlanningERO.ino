void planERO(int strategi){
  if(strategi==0){

    if(plan == 0){
      indexPos = 0;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 1){
      indexPos = 1;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 2){
      indexPos = 2;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 3){
      dribble(200);
      if(PIDBolaC(0, 30, Theta, 0, EE.SPEED[modeSpeed])){plan++;} 
    } else if(plan == 4){
      dribble(100);
      if(PIDRobot(60,10)){plan++;}
    } else if(plan == 5){
      stop(); 
      dribble(-20);  
      tendangSlow();
      plan++;
    } else if(plan == 6){
      dribble(200);
      indexPos = 3;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 7){
      indexPos = 4;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 8){ 
      if(PIDBolaC(0, yBolaC, Theta, 0, 150)){plan++;}
      if(yBolaC>0 && yBolaC<160){countBolaDekat++;}
      else{countBolaDekat=0;}
      if(countBolaDekat>2){plan++;}  
    } else if(plan == 9){ 
      if(PIDBolaC(0, yBolaC, Theta, 1, 150)){plan++;}  
      if(yBolaC<120){countBolaDekat++;}
      else{countBolaDekat=0;}
      if(countBolaDekat>2){plan++;}  
    } else if(plan == 10){ 
      if(PIDBolaC(0,30,Theta,0,150)){plan++;}
    } else if(plan == 11){
      indexPos = 3;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 12){ 
      dribble(100);
      if(PIDRobot(60,10)){plan++;} 
    } else if(plan == 13){
      stop(); 
      dribble(-20);  
      tendangSlow();
      plan++;
    } else if(plan == 14){
      indexPos = 0;
      runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed]);
    } else{
      dribble(20);
      stop();
    }
  }
}