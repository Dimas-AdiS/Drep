void parseBola() {
  float data_x, data_y,data_X, data_Y;

  char getData = SerialCamera.read();

  if (getData == 'x') {
    xBola = SerialCamera.parseInt(); //X bola bawah
    if (SerialCamera.read() == 'y') {
      yBola = SerialCamera.parseInt(); //Y bola bawah
      if (SerialCamera.read() == 'X') {
        xBola1 = SerialCamera.parseInt(); //X bola atas
        if (SerialCamera.read() == 'Y') {
          yBola1 = SerialCamera.parseInt(); //Y bola atas
          if (xBola ==-1 && yBola ==-1) {
            detekBolaB = 0;
            countDetek = 0;
          }
          else {
            detekBolaB = 1;
          } 
          if (xBola1 ==-1 && yBola1 ==-1) {
            detekBolaC = 0;
            countDetek = 0;
          }
          else {
            countGaDetekC = 0;
            detekBolaC = 1;
          } 

          // if(xBola < 0 && xBola1 < 0){
          //   countDetek = 0;
          // }
        }      
      }
          
    }
  }
}

void bolaCermin(){
//  parseBola();
  if(detekBolaC==1){
    // yBolaC = (wCermin/2) - xBola1;
    // xBolaC = (hCermin/2) - yBola1;
    yBolaC = yBola1;
    xBolaC = xBola1;
    rBolaC = 10 * sqrt((xBolaC / 10 * xBolaC / 10) + (yBolaC / 10 * yBolaC / 10)); 
    tBolaC = 0;
    
    if (xBolaC >= 0) {
      tBolaC = ((acos(yBolaC / rBolaC))*(180/PI));
    }
    else {
      tBolaC = -((acos(yBolaC / rBolaC))*(180/PI));
    }
  }else{
    xBolaC = 0;
    yBolaC = 0; 
    rBolaC = 0;
    tBolaC = 0;
  }
}

void bolaWide(){
//  parseBola();
  if(detekBolaB==1){
    // xBolaB = cXWide - xBola;
    // yBolaB = cYWide - yBola;
    xBolaB = xBola;
    yBolaB = yBola;
    rBolaB = 10 * sqrt((xBolaB / 10 * xBolaB / 10) + (yBolaB / 10 * yBolaB / 10)); 
    tBolaB = 0;
    
    if (xBolaB >= 0) {
      tBolaB =-((acos(yBolaB / rBolaB))*(180/PI));
    }
    else {
      tBolaB = ((acos(yBolaB / rBolaB))*(180/PI));
    }
  }else{
    xBolaB = 0;
    yBolaB = 0; 
    rBolaB = 0;
    tBolaB = 0;
  }
}