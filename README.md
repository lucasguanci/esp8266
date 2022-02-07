# Adafruit ESP8266 Feather Huzzah
L'**ESP8266** è un microcontrollore economico con tecnologia Wi-Fi, prodotto dalla _Espressif_ di Shangai.

L'Adafruit ESP8266 Feather Huzzah è una scheda basata sul chip ESP8266 con processore impostato a 80 MHz e tensione logica di 3.3V.

{{< insertImg align="center" url="mcu-feather-huzzah-pinout.jpg" >}}

# Connessione Wi-Fi
L'ESP8266 può stabilire una connessione Wi-Fi, in particolare supporta tre diverse modalità di connessione.

## Station mode
In modalità __station mode__ l'ESP8266 può connettersi a una rete esistente, una volta connesso all'ESP8266 verrà assegnato un indirizzo _IP address_ su quella specifica rete.
```c
// Include the Wi-Fi library
#include <ESP8266WiFi.h>        

// The SSID (name) of the Wi-Fi network you want to connect to
const char* ssid     = "TT";         
// The password of the Wi-Fi network
const char* password = "noteaspoon";     

void setup() {
	// Start the Serial communication to send messages to the computer
  	
  	Serial.begin(115200);         
	delay(10);
  	Serial.println('\n');
  	
	// Connect to the network  	
  	WiFi.begin(ssid, password);             
  	Serial.print("Connecting to ");
  	Serial.print(ssid); Serial.println(" ...");

  	int i = 0;
	// Wait for the Wi-Fi to connect  	
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
```
Se si apre il terminale sarà possibile vedere l'indirizzo associato al disponibile che risponderà correttamente al ping.

### soft-Access Point mode (AP-mode)
L'ESP8266 può essere utilizzato come _access point_ e stabilire una propria rete Wi-Fi, questo può essere utile per esempio quando sia necessario collegarsi al dispositivo attraverso una rete Wi-Fi ma non si abbia a disposizione una rete nelle vicinanze.
```c
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
```
E' possibile eseguire un ping verso il dispositivo, `ping 192.168.4.1` ma se proviamo a connetterci a un sito web riceviamo però un messaggio di errore, perché l'ESP8266 non è direttamente connesso a Internet.

### DNS and mDNS

## Web Server (station+softAP mode)
Un server web è una macchina connessa a Internet in grado di ricevere delle richieste e fornire dei dati alle macchine che li richiedono.
Per scambiare dati con un server è prima di tutto necessario stabilire una **connessione** con il server: per far questo di solito si utilizza il **protocollo HTTP** (_hyper-text transfer protocol_).

Per scrivere dati da un server si utilizza una richiesta di tipo _GET_, mentre per inviare dati a un server è necessaria una richiesta di tipo _POST_.

```c
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
// Include the WebServer library
#include <ESP8266WebServer.h>   

// Create a webserver object that listens for HTTP request on port 80
ESP8266WebServer server(80);    

// network parameter
const char* ssid = "TT";
const char* password = "noteaspoon";

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
```

### Accendere un LED via Wi-Fi
E' possibile controllare l'ESP8266 attraverso una pagina web, per esempio vediamo quale è il codice che permette di accendere un LED che si trova a bordo della scheda.

```c
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
// Include the WebServer library
#include <ESP8266WebServer.h>   

// Create a webserver object that listens for HTTP request on port 80
ESP8266WebServer server(80);    

// network parameter
const char* ssid = "Let me in";
const char* password = "remandkurt";

// function prototypes for HTTP handlers
void handleRoot();   
void handleSwitchLED();           
void handleNotFound();

void setup(void) {
	// Configure pin 0 as output and initialize it as switched-off
	pinMode(0, OUTPUT);
	delay(100);
	digitalWrite(0, LOW);

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
	server.on("/led", handleSwitchLED);
	// When a client requests an unknown URI call function "handleNotFound"
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

void handleSwitchLED() {
	// Handle the request
	digitalWrite(0, !digitalRead(0));
	server.send(200, "text/plain", "Led has been switched");   
}

void handleNotFound(){
	// Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
	server.send(404, "text/plain", "404: Not found"); 
}
```
