// Includes
#include "NetworkCreds.h"
#include "ADC.h"
#include "Indicators.h"
#include "WiFi.h"

// Libraries
#include <WiFiManager.h>


// DEFINES


// Global Variables


void setup()
{
  InitSerial();
  InitIndicator();
  InitADC();
  InitWiFi();

  if(BeginWiFiConnection())
  {
    // Connection Success.
    SetFlashRate(FR_0_25_HZ);
  }
  else
  {
    // Connection Failed. Indicate Error
    SetFlashRate(FR_ON);
  }
}

void loop()
{
  ServiceADC();
  ServiceIndicator();
}

void InitSerial(void)
{
  Serial.begin(115200);
}