#include <WiFiManager.h>
#include "NetworkCreds.h"

void setup()
{
  // Initialize WiFi Manager
  WiFi.mode(WIFI_STA);
  WiFiManager wifiManager;

  // Wipe stored credentials for testing
  // wm.resetSettings();

  // Initialize Serial
  Serial.begin(115200);

  // Initialize onboard LED
  pinMode(2, OUTPUT);
  delay(100);

  // Connect to Wi-Fi network
  if (!wifiManager.autoConnect(ssid, password)) 
  {
    Serial.println("Connection failed! Connect to ");
    Serial.println(ssid);
    Serial.println(" to configure WiFi Network Connection.");
    // Indicate connection failure
    digitalWrite(2, HIGH);
    while(1);
  }
  else
  {
    Serial.println("Connected to Wi-Fi network");
    // Indicate connection success
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(2,LOW);
    delay(2000);
  }
}

void loop()
{
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);
}