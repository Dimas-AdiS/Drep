void listenCoach() {  
  if (SerialCoach.available() > 0) {
    char data = SerialCoach.read();
    if (data == 'S' || data == 's' || data == 'R' || data == 'r') {
      intruksiPlay = data;
    } 
    else if (data == 'N' || data == 'K' || data == 'F' || data == 'G' || data == 'C' || data == 'P' || data == 'k' || data == 'f' || data == 'g' || data == 'c' || data == 'p') {
      intruksiFull = data;
    }
    else if (data == '?') {
      //aktifin ini untuk terima data rosi posisi x dan y sekarang
      data = SerialCoach.read();
      if (data == enableRobot) {
        data = SerialCoach.read();
        if (data == 'X') {
          int dataX = SerialCoach.parseInt();
          if (SerialCoach.read() == 'Y') {
            int dataY = SerialCoach.parseInt();
            if (SerialCoach.read() == '#') {
              jarX = (int)dataX;
              jarY = (int)dataY; 
            }
          }
        }
        else if (data == 'W') {
          int dataW = SerialCoach.parseInt();
          SerialGyro.println(dataW + String("#"));
          enableInisial = 'N';
        }
      }
    }  
    else if (data == '!') {
      data = SerialCoach.read();
      if (data == enableRobot) {
        data = SerialCoach.read();
        if (data == 'X') {
          int dataX = SerialCoach.parseInt();
          if (SerialCoach.read() == 'Y') {
            int dataY = SerialCoach.parseInt();
            if (SerialCoach.read() == '#') {
              xTarget = (int)dataX;
              yTarget = (int)dataY; 
            }
          }
        }
        else if (data == 'W') {
          int dataW = SerialCoach.parseInt();
          if (SerialCoach.read() == '#') {
            tTarget = dataW; 
          }
        } 
      } 
    }
    else if (data == '@') {  
      int dataIn = SerialCoach.parseInt();
      if (SerialCoach.read() == '#') {
        strategi = dataIn;  
      }
      enableInisial = 'N';
    } 
  }
}

void updateToCoach() {
  if (countMs > 20) {
    char buf[100];  
    sprintf(buf,"?,%d,%d,%d,%d,",(int)jarX,(int)jarY,(int)Theta,(int)kejarBola);
    SerialCoach.print(enableRobot); SerialCoach.print(buf);
     
    sprintf(buf,"%d,%d,%d,",(int)xTarget,(int)yTarget,(int)tTarget);
    SerialCoach.println(buf); 
    EE.EEjarX = jarX; EE.EEjarY = jarY; EEPROM.put(0, EE);
    countMs = 0; 
	//3?,1,10,11,9,1,19,14,41
  }
}