// Includes
#include "Indicators.h"
#include "Time.h"

// DEFINES
// LED is active low
#define LED_ON  LOW
#define LED_OFF HIGH


// File Scope Variables
static int IndicatorFlashRate;
static int IndicatorTimerID;
static bool IndicatorStatus;


void InitIndicator(void)
{
    pinMode(PIN_ON_BOARD_LED, OUTPUT);
    IndicatorFlashRate = FR_OFF;
    IndicatorTimerID = RegisterTimer();
    IndicatorStatus = (bool)LED_OFF;
}

void ServiceIndicator(void)
{
    if(IndicatorFlashRate < 0)
    {
        // Negative Flash Rate. Leave off.
        IndicatorStatus = (bool)LED_OFF;
    }
    else if(IndicatorFlashRate < FR_5_MS)
    {
        // Flash Rate faster than tick rate. Leave on.
        IndicatorStatus = (bool)LED_ON;
    }
    else
    {
        // Perform indicator flash pattern
        if(IsTimerExpired(IndicatorTimerID))
        {
            IndicatorStatus = !IndicatorStatus;
            SetTimer(IndicatorTimerID, IndicatorFlashRate);
        }
    }

    digitalWrite(PIN_ON_BOARD_LED, IndicatorStatus);
}

void SetFlashRate(int FlashRate)
{
    // Ensure indicator updates on next service.
    IndicatorFlashRate = FlashRate;
    ClearTimer(IndicatorTimerID);
}
