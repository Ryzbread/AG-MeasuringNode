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
static int SoilMoistureData;

void setup()
{
    SoilMoistureData = 0;

    // Call this before everything else.
    InitTime();

    // The initial WiFi connection takes a few seconds
    InitSerial();
    InitIndicator();
    InitADC();
    InitWiFi();
    BeginWiFiConnection();
    InitWiFiConnection();

    // Indicate connection status
    if(GetConnectionStatus())
    {
        // Connection Success.
        SetFlashRate(FR_0_25_HZ);
    }
    else
    {
        // No connection. Indicate setup is required.
        SetFlashRate(FR_ON);
    }
}

void loop()
{
    // Operate everything on Tick Time
    if(ServiceTime())
    {
        ServiceADC();
        SoilMoistureData = GetADCReading(); // TODO: Normalize raw ADC data to 0-100%

        ServiceIndicator();

        ServiceWiFiConnection(SoilMoistureData);
    }
}

void InitSerial(void)
{
    Serial.begin(115200);
}