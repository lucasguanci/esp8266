# Adafruit ESP8266 Feather Huzzah
**ESP8266** is a budget Wi-Fi enabled microncontroller manifactured by the Shangai-based company Espressif.
The Adafruit ESP8266 Feather Huzzah board is based on the ESP8266 chip, running at 80 MHz with logic tension of 3.3V.

## Wi-Fi connection
ESP8266 has three different connection modes, 
- _station mode_;
- _soft-Access Point mode_;
- _Web Server_ (soft-AP + station) mode;

In the repository you may find projects exploring the three connection modes, in particular:
- **esp8266-station-mode** is a basic code to connect the microcontroller to an existent Wi-Fi network;
- **esp8266-softAP** create a soft-Access Point;
- **esp8266-web-server** connects to a Wi-Fi network and run a basic web server on the micro;
- **esp8266-web-server-led** connects to a Wi-Fi network and run a simple web server able to toggle the #0 led on the micro using a GET request;
- **esp8266-rgb-led-control-app** creates a soft-Access Point and run a web server to control an RGB led; a browser can connect to the server using a web app based on the WebSocket API
- **mini-R** is a web-app used to control a mini rover

## mini-R
**mini-R** is a Wi-Fi controlled robot based on the [Adafruit Mini Robot Rover Chassis Kit, 2WD with DC Motors](https://www.adafruit.com/product/2939).
At the core of the project lays an Adafruit ESP8266 Feather Huzzah running in soft-AP mode controlled by a web-app.

### Controlling the rover
The rover hosts a web server that creates an interface to enable mini-R's movements.
The HTML5/CSS web app is based on the WebSocket API. The app is written using vanilla-JavaScript and the entire code can be run without the need for any external library – an Internet connection is not required.
