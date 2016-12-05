#HomeKit Demo ESP8266 Setup

Basic Example of how to control sensors by ESP8266 and expose this sensors to the API

## Getting Started

1. [Download Arduino IDE](https://www.arduino.cc/en/Main/Software) - make sure that it is from arduino.cc, otherwise you won't be able to add additional board managers
2. Open "ESP8266_test.ino" file in arduino IDE
2. Go to Arduino IDE preferences and add this link [http://arduino.esp8266.com/stable/package_esp8266com_index.json](http://arduino.esp8266.com/stable/package_esp8266com_index.json) to "Additional Boards Managers URLs"
3. Go to Tools -> Board -> Board Managers and install "esp8266"
4. Go to Sketch -> Include Library -> Library Manager and download all of the following libraries:
  ```
  #include <aREST.h>
  #include <aREST_UI.h>
  #include <OneWire.h>
  #include <DallasTemperature.h>

  //If you want to work with servo machine then download also this Library
  #include <Servo.h> 
  ```
5. Add your WiFi Name and Password to following fields:
  ```
  const char* ssid = "YOUR_WIFI_NETWORK_NAME";
  const char* password = "YOUR_WIFI_PASSWORD";

  ```
6. Change to your pins where it is needed
7. Connect your device, Verify and Upload Code to you Device board
8. Now if you open your serial monitor you should see that device is connected to your WiFi with particular address, use this address in your browser and you should see Rest UI for you device control.
9. Enjoy! 
