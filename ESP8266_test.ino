// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h> 

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 12

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Create Servo instance
/*Servo myservo;*/

// Create aREST instance
aREST_UI rest = aREST_UI();

// WiFi parameters
const char* ssid = "YOUR_WIFI_NETWORK_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
float temperature;

int ledControl(String command);
int coffeeControl(String command);

void setup(void) {
  sensors.begin();

  // Start Serial
  Serial.begin(115200);

  // Set the title
  rest.title("aREST UI Demo");

  // Create button to control pin 5 and 13 you should provide your pins here
  rest.button(5);
  rest.button(13);

  //for servo you should attach 
  /*myservo.attach(4);*/

  // Init variables and expose them to REST API
  rest.variable("temperature", &temperature);

  // Labels
  rest.label("temperature");

  // Function to be exposed
  rest.function("led", ledControl);
  rest.function("ledTwo", coffeeControl);

  //if you want to play with servo machine
  //it will be available by YOUR_DEVICE_IP_ADDRESS/servo?params=YOUR_VALUE (0 to 255)
  /*rest.function("servo", servoControl);*/

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);

  sensors.requestTemperatures(); // Send the command to get temperatures
  temperature = sensors.getTempCByIndex(0);
}

int coffeeControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(13, state);
  return 1;
}

int ledControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(5, state);
  return 1;
}

/*int servoControl(String command) {*/
  /*Serial.println(command);*/
  /*int state = command.toInt();*/
  /*myservo.write(state);*/
/*}*/
