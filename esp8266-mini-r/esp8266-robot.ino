/*
   luca sguanci – idrovolante.org
   january/february, 2022

  based on Adafruit ESP8266 Feather Huzzah and Adafruit Modtor Shield, see:
  - https://learn.adafruit.com/bluefruit-feather-robot
  - 

*/

// AF Motor Shield
#include <Wire.h>
#include <Adafruit_MotorShield.h>
// ESP8266 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
// Include web-app
#include "esp8266-robot-app.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);

// Create a webserver object that listens for HTTP request on port 80
ESP8266WebServer server(80);
// create a websocket server on port 81
WebSocketsServer webSocket(81);

// The name of the Wi-Fi network that will be created
const char *ssid = "mini-R";
// The password required to connect to it, leave blank for an open network
const char *password = "kurtandcurtney";

// Commands send through WebSocket
static const char rFW[] = "rForward";
static const char rBW[] = "rBackward";
static const char rLT[] = "rLeft";
static const char rRT[] = "rRight";
static const char rST[] = "rStop";

// the pins with LEDs connected are outputs
void setup() {
  Serial.begin(9600);

  // start AFMS and warm up motors
  // create with the default frequency 1.6KHz
  AFMS.begin();  
  startMotors();
  
  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);

  // configure the ESP8266 in soft-Access Point
  startWiFi();
  
  // Start a WebSocket server
  startWebSocket();
  
  // Start a HTTP server
  startServer();
}

void loop() {
  // constantly check for websocket events
  webSocket.loop();

  // run the server
  server.handleClient();
}

void startMotors() {
  L_MOTOR->setSpeed(0);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(0);
  R_MOTOR->run(RELEASE);
}

// Start a Wi-Fi access point
void startWiFi() {
  // Start the access point
  WiFi.softAP(ssid, password);
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started\r\n");

  Serial.print("IP address:\t");
  // Send the IP address of the ESP8266 to the computer
  Serial.println(WiFi.softAPIP());
}

// Start a WebSocket server
void startWebSocket() {
  // start the websocket server
  webSocket.begin();
  // if there's an incomming websocket message, go to function 'webSocketEvent'
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started.");
}

// Start a HTTP server with a file read handler and an upload handler
void startServer() {
  server.on("/", handleRoot);  
  server.onNotFound(handleNotFound);          // if someone requests any other file or page, go to function 'handleNotFound'

  // start the HTTP server
  server.begin();
  Serial.println("HTTP server started.");
}

void handleRoot() {
  String htmlPage = webpageCode; 
  server.send(200, "text/html", htmlPage);
}

// if the requested file or page doesn't exist, return a 404 not found error
void handleNotFound(){
  server.send(404, "text/plain", "404: File Not Found");
}

// When a WebSocket message is received
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
  switch (type) {
    // if the websocket is disconnected
    case WStype_DISCONNECTED:            
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    // if a new websocket connection is established
    case WStype_CONNECTED: {             
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    // if new text data is received
    case WStype_TEXT:                    
      Serial.printf("[%u] get Text: %s\n", num, payload);
      if ( strcmp( (const char *)payload, rFW)==0 ) {
        // move forward
        Serial.println("Move forward");
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(FORWARD);
      } else if ( strcmp((const char *)payload, rBW)==0 ) {
        // move backward
        Serial.println("Move backward");
        L_MOTOR->run(BACKWARD);
        R_MOTOR->run(BACKWARD);
      } else if (strcmp((const char *)payload, rLT)==0) {
        // turn left
        Serial.println("Turn left");
        L_MOTOR->run(RELEASE);
        R_MOTOR->run(FORWARD);
      } else if (strcmp((const char *)payload, rRT)==0) {
        // turn right
        Serial.println("Turn right");
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(RELEASE);
      } else if (strcmp((const char *)payload, rST)==0) {
        // halt the robot
        Serial.println("Halting");
        L_MOTOR->run(RELEASE);
        R_MOTOR->run(RELEASE);
      }
      R_MOTOR->setSpeed(150);
      L_MOTOR->setSpeed(150);
      break;
    default:
      Serial.printf("Invalid WStype [%d]\r\n", type);
      break;
  }
}
