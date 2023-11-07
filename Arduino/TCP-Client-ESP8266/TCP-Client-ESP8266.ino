#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

const uint16_t port = 1119; //PC  
//const uint16_t port = 28097; //juri 
 
//const char * host = "192.168.0.106"; //laptop iqbal wifi USEROSJUARA
//const char * host = "192.168.0.107"; //laptopku wifi USEROSJUARA
//const char * host = "10.20.3.135"; //laptopku wifi Free Wifi USM 1
const char * host = "172.16.47.1"; //WiFi KRSBI BERODA


char data[30],dataIn[30],x=0;
String dataKirim;

int X, Y,Theta;
int count;
    
void setup() { 
    Serial.begin(115200);
    delay(10);
    pinMode(2,OUTPUT);

    WiFi.mode(WIFI_STA); 
//    WiFiMulti.addAP("Free Wifi USM 1", "");
    WiFiMulti.addAP("KRSBI BERODA", "KRSBI_2022");
//    WiFiMulti.addAP("USEROSJUARA", "11022019");
//    WiFiMulti.addAP("KRI-BERODA-2Ghz", "beroda2019");

    while(WiFiMulti.run() != WL_CONNECTED) { 
        digitalWrite(2,HIGH);
        delay(250);
        digitalWrite(2,LOW);
        delay(250);
    }

//    Serial.println("");
    delay(500);

    client.connect(host, port);   

//  Serial.println(WiFi.macAddress());
}

void loop() {
    if (!client.connect(host, port)) {
      return;
      digitalWrite(2,HIGH);
      
      while(WiFiMulti.run() != WL_CONNECTED) {
        digitalWrite(2,HIGH);
        delay(250);
        digitalWrite(2,LOW);
        delay(250);
      }
      delay(200);
      client.connect(host, port);
      
    }    
    digitalWrite(2,LOW);

  while(client.connected()){
    
    while(Serial.available()>0){
      dataIn[x] = Serial.read();
      x++;
      if(dataIn[x-1] == '\n'){
        x=0;
        dataKirim = dataIn;
        client.print(dataKirim);
      }
    }

    if(client.available()){
      char data = client.read();
      String data1 = String(data);
      Serial.print(data1);
      if(data == 'K'){digitalWrite(2,HIGH); Serial.print("KK");}
      if(data == 'k'){digitalWrite(2,LOW); Serial.print("kk");}
      if(data == 'F'){digitalWrite(2,HIGH); Serial.print("FF");}
      if(data == 'f'){digitalWrite(2,LOW); Serial.print("ff");}
      if(data == 'G'){digitalWrite(2,HIGH); Serial.print("GG");}
      if(data == 'g'){digitalWrite(2,LOW); Serial.print("gg");}
      if(data == 'C'){digitalWrite(2,HIGH); Serial.print("CC");}
      if(data == 'c'){digitalWrite(2,LOW); Serial.print("cc");}
      if(data == 'P'){digitalWrite(2,HIGH); Serial.print("PP");}
      if(data == 'p'){digitalWrite(2,LOW); Serial.print("pp");}
      if(data == 's'){digitalWrite(2,HIGH); Serial.print("ss");}
      if(data == 'S'){digitalWrite(2,LOW); Serial.print("SS");}
      if(data == 'N'){digitalWrite(2,HIGH); Serial.print("NN");}
      if(data == 'Q'){digitalWrite(2,LOW); Serial.print("QQ");}
      if(data == 'E'){digitalWrite(2,HIGH); Serial.print("EE");}
      if(data == 'B'){digitalWrite(2,LOW); Serial.print("BB");}
      if(data == 'b'){digitalWrite(2,HIGH); Serial.print("bb");}
      if(data == 'D'){digitalWrite(2,LOW); Serial.print("DD");}
      if(data == 'd'){digitalWrite(2,HIGH); Serial.print("dd");}

         if(data == 'd'){digitalWrite(2,HIGH); Serial.print("dd");}
   
    }
// rfrrfrfrf
  }
}
