# mini-R

**mini-R** is a Wi-Fi controlled robot based on the [Adafruit Mini Robot Rover Chassis Kit, 2WD with DC Motors](https://www.adafruit.com/product/2939).
At the core of the project lays an Adafruit ESP8266 Feather Huzzah running in soft-AP mode controlled by a web-app.

## Controlling the rover
The rover host a web server that creates an interface to enable mini-R's movements.
The HTML5/CSS web app is based on the WebSocket API. The app is written using vanilla-JavaScript so that the entire code can be run on the web server hosted by the rover itself without the need for any external library.