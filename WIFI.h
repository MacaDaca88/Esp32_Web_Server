//#include <WiFi.h>

const char *ssid = "Tip-jar";             // WiFi network name
const char *password = "PASSWORD1234LOL"; // WiFi network password

void WIFIconnection() {
  WiFi.mode(WIFI_STA);                     // Set WiFi mode to station (client)
  WiFi.begin(ssid, password);              // Connect to WiFi network
  
  // Attempt to connect to WiFi
  Serial.print("Connecting to WiFi...");
  printToSerialAndWeb("Connecting to WiFi...");

  // Wait for the connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");                      // Print dots to indicate connection attempt
    printToSerialAndWeb(".");               // Stream dots to the webpage
  }

  // Successful connection feedback
  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  printToSerialAndWeb("\nConnected to WiFi");
  printToSerialAndWeb("IP address: " + WiFi.localIP().toString());
}
