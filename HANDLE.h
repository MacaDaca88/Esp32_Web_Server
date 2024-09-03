// Function to send serial data to the webpage
void handleSerialData() {
  server.sendHeader("Cache-Control", "no-cache");
  Serial.println("Sending to web: " + serialData);  // Debug print
  server.send(200, "text/event-stream", "data: " + serialData + "\n\n");
  serialData = "";  // Clear data after sending
}

// Function to send LED state to the webpage
void handleLedState() {
  String state = ledState ? "LED is ON" : "LED is OFF";
  server.send(200, "text/event-stream", "retry: 5000\n"
                                        "data: "
                                          + state + "\n\n");
}

// Display serial data on both serial monitor and webpage
void printToSerialAndWeb(const String& message) {
  Serial.println(message);       // Print to the Serial Monitor
  serialData += message + "\n";  // Store the message for streaming to the webpage
}
