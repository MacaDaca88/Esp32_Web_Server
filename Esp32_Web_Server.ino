
#include "OTA.h"        // Handles OTA updates
#include <WebServer.h>  // Web server library

#define LED 5

WebServer server(80);  // Create a web server object on port 80

String serialData = "";  // Store serial data for streaming
bool ledState = false;   // Variable to store LED state

#include "HANDLE.h"   // Contains route handlers and helper functions
#include "SENSORS.h"  // Contains sensor setup and loop functions
#include "WEB_PAGE.h" // Contains web page HTML content or related functions

void setup() {
  Serial.begin(115200);
  OTA_setup();        // Initialize OTA updates
  SENSORsetup();      // Initialize sensors
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);  // Turn off the LED initially

  // Define server routes
  server.on("/", handleRoot);
  server.on("/ledOn", handleLedOn);
  server.on("/ledOff", handleLedOff);
  server.on("/ledState", handleLedState);    // Route for LED state stream
  server.on("/serial", handleSerialData);    // Route for serial data stream

  // Start the server
  server.begin();
  printToSerialAndWeb("Web server started");
}

void loop() {
  OTA_loop();         // Handle OTA updates
  SENSORloop();       // Read sensor data and process
  server.handleClient();  // Handle client requests
}

// Function to handle turning the LED on
void handleLedOn() {
  digitalWrite(LED, HIGH);  // Turn LED on
  printToSerialAndWeb("ON");
  ledState = true;
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect to the main page
}

// Function to handle turning the LED off
void handleLedOff() {
  digitalWrite(LED, LOW);  // Turn LED off
  printToSerialAndWeb("OFF");
  ledState = false;
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect to the main page
}
