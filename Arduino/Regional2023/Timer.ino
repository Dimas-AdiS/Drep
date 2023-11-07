void initTimer() {
  MsTimer2::set(millisInterrupt, timerInterrupt);
  MsTimer2::start();
}

void timerInterrupt() {
  countInterrupt++;
  countMs++;

  jar1 = jarPerPulsa * freqEncoder1;
  jar2 = jarPerPulsa * freqEncoder2;
  jar3 = jarPerPulsa * freqEncoder3; 
  
  freqEncoder1 = 0;
  freqEncoder2 = 0;
  freqEncoder3 = 0;

  updateJarak();

  if(countInterrupt>=convertInterrupt){
    detikMain++;
    countInterrupt = 0;
  }
  
  countTendang++;
}