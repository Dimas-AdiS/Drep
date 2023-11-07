#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

const char* ssid = "Kkrbt";
const char* password = "Kkrbt2023";
const char* webSocketServerAddress = "192.168.9.224";
const int webSocketServerPort = 8000;

WebSocketsClient webSocket;
ESP8266WiFiMulti WiFiMulti; 

void setup() {
  Serial.begin(115200);
  WiFiMulti.addAP(ssid, password); 

  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(100);
  }

  Serial.println("Connected to WiFi");

  webSocket.begin("192.168.9.224", 8000, "/ws");
  webSocket.onEvent(webSocketEvent); 
  webSocket.setReconnectInterval(5000); 
  webSocket.enableHeartbeat(15000, 3000, 2);
}

void loop() {
  webSocket.loop();

//  if (!webSocket.isConnected()) {
//    reconnectWebSocket();
//  }

  // Send data to the server
  sendSensorData();
  delay(1000);
}

void reconnectWebSocket() {
  while (!webSocket.isConnected()) {
    Serial.println("Trying to reconnect to WebSocket server...");
//    webSocket.connect(); 
    webSocket.begin(webSocketServerAddress, webSocketServerPort, "/ws");
    delay(1000);
  }
}

void sendSensorData() {
  // Read sensor data
  float sensorValue = analogRead(A0) / 1023.0 * 5.0;

  // Create JSON payload
  DynamicJsonDocument jsonDoc(128);
  jsonDoc["type"] = "dataFront";
  jsonDoc["source"] = "ESP32";
  jsonDoc["data"] = sensorValue;
  
  // Serialize JSON to a string
  String payload;
  serializeJson(jsonDoc, payload);
  
  // Send payload to the server
  webSocket.sendTXT(payload);
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket disconnected");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket connected");
      break;
    case WStype_TEXT:
      // Handle incoming messages from the server
      handleMessage(payload, length);
      break;
    default:
      break;
  }
}

void handleMessage(uint8_t* payload, size_t length) {
  // Parse incoming JSON message
  DynamicJsonDocument jsonDoc(128);
  deserializeJson(jsonDoc, payload, length);

  String messageType = jsonDoc["type"].as<String>();

  if (messageType == "message") {
    String messageData = jsonDoc["data"].as<String>();
    Serial.println("Received message from server: " + messageData);
  }
}
