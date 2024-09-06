
#include <Adafruit_NeoPixel.h>
#include "OTA.h"        // Handles OTA updates
#include <WebServer.h>  // Web server library


WebServer server(80);  // Create a web server object on port 80

String serialData = "";  // Store serial data for streaming

#include "HANDLE.h"    // Contains route handlers and helper functions
#include "SENSORS.h"   // Contains sensor setup and loop functions
#include "WEB_PAGE.h"  // Contains web page HTML content or related functions
#include "LED.h"


void setup() {
  Serial.begin(115200);
  OTA_setup();    // Initialize OTA updates
  SENSORsetup();  // Initialize sensors
  LEDsetup();

  // Define server routes
  server.on("/", handleRoot);
  server.on("/ledOn", handleLedOn);
  server.on("/ledOff", handleLedOff);
  server.on("/ledState", handleLedState);  // Route for LED state stream
  server.on("/serial", handleSerialData);  // Route for serial data stream
  server.on("/setRGB", handleSetRGB);      // Route for setting RGB values
  server.begin();                          // Start the server
  printToSerialAndWeb("Web server started");
}

void loop() {
  OTA_loop();             // Handle OTA updates
  SENSORloop();           // Read sensor data and process
  server.handleClient();  // Handle client requests
}
