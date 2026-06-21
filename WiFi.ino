// Includes
#include "NetworkCreds.h"


// Libraries
#include <WiFiManager.h>


// DEFINES


// Global Variables
static WiFiManager wifiManager;


void InitWiFi(void)
{
  // Wipe stored credentials for testing
  // wm.resetSettings();

  WiFi.mode(WIFI_STA);
}

bool BeginWiFiConnection(void)
{
  bool ConnectionSuccess = false;

  // Connect to Wi-Fi network
  if (!wifiManager.autoConnect(ssid, password)) 
  {
    Serial.println("Connection failed! Connect to ");
    Serial.println(ssid);
    Serial.println(" to configure WiFi Network Connection.");
  }
  else
  {
    Serial.println("Connected to Wi-Fi network");
    ConnectionSuccess = true;
  }

  return ConnectionSuccess;
}