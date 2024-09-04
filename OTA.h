#include <WiFi.h>
#include <ESPmDNS.h>       // Include for mDNS support
#include <ArduinoOTA.h>    // Include for OTA functionalities

// WiFi credentials
const char* ssid = "Tip-jar";          // Define WiFi SSID only here
const char* password = "PASSWORD1234LOL"; // Define WiFi Password only here

void OTA_setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  Serial.println("Booting");

  // Set WiFi to station mode and attempt to connect
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);  

  // Retry connection if it fails
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // OTA setup configurations
  ArduinoOTA.setHostname("WebServer");  // Set OTA Hostname
  ArduinoOTA.setPassword("Created");

  ArduinoOTA
      .onStart([]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
        Serial.println("Start updating " + type);
      })
      .onEnd([]() {
        Serial.println("\nEnd");
      })
      .onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        switch (error) {
          case OTA_AUTH_ERROR: Serial.println("Auth Failed"); break;
          case OTA_BEGIN_ERROR: Serial.println("Begin Failed"); break;
          case OTA_CONNECT_ERROR: Serial.println("Connect Failed"); break;
          case OTA_RECEIVE_ERROR: Serial.println("Receive Failed"); break;
          case OTA_END_ERROR: Serial.println("End Failed"); break;
        }
      });

  ArduinoOTA.begin();  // Start OTA service

}

void OTA_loop() {
  ArduinoOTA.handle();  // Regularly call this in the main loop to handle OTA updates
}

