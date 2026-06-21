// Includes
#include "Indicators.h"

// DEFINES


// File Scope Variables
static int IndicatorFlashRate;


void InitIndicator(void)
{
  pinMode(PIN_ON_BOARD_LED, OUTPUT);
  IndicatorFlashRate = FR_0_5_HZ;
}

void ServiceIndicator(void)
{
  if(IndicatorFlashRate == FR_ON)
  {
    digitalWrite(PIN_ON_BOARD_LED, HIGH);
  }
  else
  {
    // TODO: Remove blocking delays
    digitalWrite(PIN_ON_BOARD_LED, HIGH);
    delay(IndicatorFlashRate);
    digitalWrite(PIN_ON_BOARD_LED, LOW);
    delay(IndicatorFlashRate);
  }
}

void SetFlashRate(int FlashRate)
{
    IndicatorFlashRate = FlashRate;
}
