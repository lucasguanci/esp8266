#include <ESP8266WiFi.h>
#include <WiFiClient.h>
// Include the WebServer library
#include <ESP8266WebServer.h>   

// Create a webserver object that listens for HTTP request on port 80
ESP8266WebServer server(80);    

// network parameter
const char* ssid = "test";
const char* password = "untepertutti";

// function prototypes for HTTP handlers
void handleRoot();              
void handleNotFound();

void setup(void){
  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);         
  delay(10);
  Serial.println('\n');

  // connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.println("Connecting ...");
  int i = 0;
  // Wait for the Wi-Fi to connect
  while ( WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print('++i');
    Serial.print(' ');
  }
  Serial.println('\n');

  // Tell us what network we're connected to
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              
  Serial.print("IP address:\t");
  // Send the IP address of the ESP8266 to the computer
  Serial.println(WiFi.localIP());           

  // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/", handleRoot);               
  // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.onNotFound(handleNotFound);        

  // Actually start the server
  server.begin();                           
  Serial.println("HTTP server started");
}

void loop(void){
  // Listen for HTTP requests from clients
  server.handleClient();                    
}

void handleRoot() {
  // Send HTTP status 200 (Ok) and send some text to the browser/client
  server.send(200, "text/plain", "Hello world!");   
}

void handleNotFound(){
  // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
  server.send(404, "text/plain", "404: Not found"); 
}
