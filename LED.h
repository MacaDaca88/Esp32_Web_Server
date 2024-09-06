


#define LED 5
#define LED_PIN 17  // Define the pin where the WS2812B is connected
#define NUM_LEDS 8  // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool ledState = false;   // Variable to store LED state


void LEDsetup() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);  // Turn off the LED initially
  strip.begin();           // Initialize the LED strip
  strip.show();            // Initialize all pixels to 'off'
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
// Function to handle RGB value updates
void handleSetRGB() {
  if (server.hasArg("values")) {
    String rgbValues = server.arg("values");
    int red, green, blue;
    sscanf(rgbValues.c_str(), "%d,%d,%d", &red, &green, &blue);

    // Update LED strip color
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    strip.show();

    printToSerialAndWeb("RGB values set to: " + rgbValues);
    server.send(200, "text/plain", "RGB values set to: " + rgbValues);
  } else {
    server.send(400, "text/plain", "Missing RGB values");
  }
}