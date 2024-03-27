// Include WiFi Library
#include <Arduino.h>
#include "WiFi.h"
 
void setup() {
 
  // Setup Serial Monitor
  Serial.begin(115200);
 
  // Put ESP32 into Station mode
  WiFi.mode(WIFI_MODE_STA);
 
  // Print MAC Address to Serial monitor
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}
 
void loop() {
 
}