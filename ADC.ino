// Includes
#include "ADC.h"


// DEFINES
#define PIN_ADC           0
#define ADC_BUFFER_LENGTH 10


// Global Variables
int ADCBuffer[ADC_BUFFER_LENGTH];
int ADCBufferIndex;
int AverageADCValue;


void InitADC(void)
{
  int ADCSeed = analogRead(PIN_ADC);

  // Initialize ADC Buffer
  for(ADCBufferIndex = 0; ADCBufferIndex < ADC_BUFFER_LENGTH; ADCBufferIndex++)
  {
    // Seed buffer with current ADC reading
    ADCBuffer[ADCBufferIndex] = ADCSeed;
  }
  ADCBufferIndex = 0;
}

void ServiceADC(void)
{
  int TempIndex = 0;
  int CurrentADCValue = analogRead(PIN_ADC);

  // Load ADC value into the buffer
  ADCBuffer[ADCBufferIndex++] = CurrentADCValue;

  if(ADCBufferIndex == ADC_BUFFER_LENGTH)
  {
    ADCBufferIndex = 0;
  }

  // Calculate rolling average ADC reading value
  AverageADCValue = 0;
  for(TempIndex = 0; TempIndex < ADC_BUFFER_LENGTH; TempIndex++)
  {
    AverageADCValue += ADCBuffer[TempIndex];
  }
  AverageADCValue = (AverageADCValue / ADC_BUFFER_LENGTH);

  Serial.print("Raw ADC Value: ");
  Serial.print(CurrentADCValue);
  Serial.print("\tAverage ADC Value: ");
  Serial.println(AverageADCValue);
}

int GetADCReading(void)
{
  return AverageADCValue;
}
