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
      indexPos = 3;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    } else if(plan == 4){
      indexPos = 4;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    }else if(plan == 5){
      indexPos = 5;
      if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
    }else if (plan == 6){
      indexPos = 0;
      runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed]);
    } 
  }
  
  // if (strategi==1){
  //     if(plan == 1){
  //     indexPos = 0;
  //     if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
  //   } else if(plan == 1){
  //     indexPos = 1;
  //     if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
  //   } else if(plan == 2){
  //     indexPos = 2;
  //     if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
  //     } else if(plan == 3){
  //       indexPos = 3;
  //     if(runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed])){plan++;};
  //    } else if(plan == 4){
  //     indexPos = 0;
  //     runKinematics(xTargetPlan[indexPos], yTargetPlan[indexPos], tTargetPlan[indexPos], EE.SPEED[modeSpeed]);
  //   } 
  }

