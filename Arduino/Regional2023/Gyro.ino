void parseGyro() {
  int dataG;
  while (SerialGyro.available() > 0) {
    int inChar = SerialGyro.read();

    if (inChar != '\n') {
      inString += (char)inChar;
    }
    else {
      dataGyro = inString.toFloat();
      inString = "";
    }
  }
}

void kirimKeGyro(int data){ 
  SerialGyro.print(data); SerialGyro.println("#");
}