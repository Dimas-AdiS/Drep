void initMotor(){
  pinMode(pwmM1_1, OUTPUT);
  pinMode(pwmM1_2, OUTPUT);
  pinMode(pwmM2_1, OUTPUT);
  pinMode(pwmM2_2, OUTPUT);
  pinMode(pwmM3_1, OUTPUT);
  pinMode(pwmM3_2, OUTPUT);
  pinMode(pwmM4_1, OUTPUT);
  pinMode(pwmM4_2, OUTPUT);
  pinMode(pwmD_1, OUTPUT);
  pinMode(pwmD_2, OUTPUT);
  pinMode(pinEnableMotor, OUTPUT);
  // disableMotor;
}

void pwmMotor(int pwm1, int pwm2, int pwm3, int pwm4){
  if(pwm1<0){
    analogWrite(pwmM1_1,-pwm1);
    analogWrite(pwmM1_2, 0);
  } else if(pwm1>0){
    analogWrite(pwmM1_1, 0);
    analogWrite(pwmM1_2,pwm1);
  } else{
    digitalWrite(pwmM1_1, 0);
    digitalWrite(pwmM1_2, 0);
  }

  if(pwm2<0){
    analogWrite(pwmM2_1,-pwm2);
    analogWrite(pwmM2_2, 0);
  } else if(pwm2>0){
    analogWrite(pwmM2_1, 0);
    analogWrite(pwmM2_2, pwm2);
  } else{
    digitalWrite(pwmM2_1, 0);
    digitalWrite(pwmM2_2, 0);
  }
  
  if(pwm3<0){
    analogWrite(pwmM3_1,-pwm3);
    digitalWrite(pwmM3_2, 0);
  } else if(pwm3>0){
    analogWrite(pwmM3_1, 255-pwm3);
    digitalWrite(pwmM3_2, 1);
  } else{
    digitalWrite(pwmM3_1, 0);
    digitalWrite(pwmM3_2, 0);
  }

  if(pwm4<0){
    digitalWrite(pwmM4_1, 1);
    analogWrite(pwmM4_2, 255+pwm4);
  } else if(pwm4>0){
    digitalWrite(pwmM4_1, 0);
    analogWrite(pwmM4_2, pwm4);
  } else{
    digitalWrite(pwmM4_1, 0);
    digitalWrite(pwmM4_2, 0);
  }
}

void stop(){
  pwmMotor(0,0,0,0);
}

void dribble(int pwmL){ 
  if(pwmL>0){
    analogWrite(pwmD_1, pwmL);
    digitalWrite(pwmD_2, 0);
  } else if(pwmL<0){
    analogWrite(pwmD_1, 255+pwmL);
    digitalWrite(pwmD_2, 1);
  } else{
    digitalWrite(pwmD_1, 0);
    digitalWrite(pwmD_2, 0);
  }
 
}
