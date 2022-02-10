// Include the Wi-Fi library
#include <ESP8266WiFi.h>        

// The name of the Wi-Fi network that will be created
const char* ssid = "ESP8266 Access Point"; 
// The password required to connect to it, leave blank for an open network
const char* password = "thereisnospoon";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  // Start the access point 
  // the ESP8266 AP will be given the default address 192.168.4.1   
  WiFi.softAP(ssid, password);
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  // Send the IP address of the ESP8266 to the computer
  Serial.println(WiFi.softAPIP());
}

void loop() {}