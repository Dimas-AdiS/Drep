void initEncoder(){
  pinMode(intPin1, INPUT_PULLUP);
  pinMode(intPin2, INPUT_PULLUP);
  pinMode(intPin3, INPUT_PULLUP);
  pinMode(digPin1, INPUT_PULLUP);
  pinMode(digPin2, INPUT_PULLUP);
  pinMode(digPin3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(intPin1), interrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(intPin2), interrupt2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(intPin3), interrupt3, CHANGE);
}

void interrupt1() {
  if (digitalRead(intPin1) == digitalRead(digPin1)) {
    countEncoder1++;  
    freqEncoder1++;
  }
  else {
    countEncoder1--;  
    freqEncoder1--;
  }
}
void interrupt2() {
  if (digitalRead(intPin2) == digitalRead(digPin2)) {
    countEncoder2++; 
    freqEncoder2++;
  }
  else {
    countEncoder2--; 
    freqEncoder2--;
  }
}
void interrupt3() {
  if (digitalRead(intPin3) == digitalRead(digPin3)) {
    countEncoder3++; 
    freqEncoder3++;
  }
  else {
    countEncoder3--; 
    freqEncoder3--;
  }
}

