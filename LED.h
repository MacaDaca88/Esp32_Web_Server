


#define LED 5


void LEDsetup() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);  // Turn off the LED initially
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
