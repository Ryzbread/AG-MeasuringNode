// Includes
#include "NetworkCreds.h"
#include "ADC.h"
#include "Indicators.h"
#include "WiFi.h"
#include "Time.h"

// Libraries
#include <WiFiManager.h>


// DEFINES


// Filescope Variables


void setup()
{
  // The initial WiFi connection takes a few seconds
  // Call first to avoid time loss for other tasks.
  InitSerial();
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

  // Call this before everything else.
  InitTime();

  InitIndicator();
  InitADC();
  SetFlashRate(FR_OFF);
}

void loop()
{
  // Operate everything on Tick Time
  if(ServiceTime())
  {
    ServiceADC();
    ServiceIndicator();
  }
}

void InitSerial(void)
{
  Serial.begin(115200);
}