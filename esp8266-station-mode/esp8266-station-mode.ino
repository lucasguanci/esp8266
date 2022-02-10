// Include the Wi-Fi library
#include <ESP8266WiFi.h>        

// The SSID (name) of the Wi-Fi network you want to connect to
const char* ssid     = "test";         
// The password of the Wi-Fi network
const char* password = "untepertutti";     

void setup() {
  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);         
  delay(10);
  Serial.println('\n');
    
  // Connect to the network   
  WiFi.begin(ssid, password);             
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  // Wait for the Wi-Fi to connect    
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  // Send the IP address of the ESP8266 to the computer
  Serial.println(WiFi.localIP());
}

void loop() {
  ;
}