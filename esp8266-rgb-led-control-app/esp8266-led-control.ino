#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

// Include web-app
#include "led-control-app.h"

// Create a webserver object that listens for HTTP request on port 80
ESP8266WebServer server(80);
// create a websocket server on port 81
WebSocketsServer webSocket(81);

// The name of the Wi-Fi network that will be created
const char *ssid = "ESP8266 Access Point";
// The password required to connect to it, leave blank for an open network
const char *password = "thereisnospoon";

// specify the pins with an RGB LED connected
#define LED_RED     15
#define LED_GREEN   13
#define LED_BLUE    12

// the pins with LEDs connected are outputs
void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);
  delay(1000);

  // Start a Wi-Fi access point
  startWiFi();
  
  // Start a WebSocket server
  startWebSocket();
  
  // Start a HTTP server with a file read handler and an upload handler
  startServer();
}

void loop() {
  // constantly check for websocket events
  webSocket.loop();

  // run the server
  server.handleClient();
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
      // we get RGB data as hex #rrggbb string
      int number = (int) strtol((const char *) &payload[1], NULL, 16);
      // int number = (int) strtol( &payload[1], NULL, 16);

      // Split them up into r, g, b values
      int red = (int) ((number >> 16) * 1024.0/255.0);
      int green = (int) ((number >> 8 & 0xFF) * 1024.0/255.0);
      int blue = (int) ((number & 0xFF) * 1024.0/255.0);
      Serial.printf("(R:%d, G:%d, B:%d)\n",red, green, blue);

      analogWrite(LED_RED,   red);
      analogWrite(LED_GREEN, green);
      analogWrite(LED_BLUE,  blue);
      break;
  }
}
