// Includes
#include "ADC.h"
#include "Time.h"


// DEFINES
#define PIN_ADC           0
#define ADC_BUFFER_LENGTH 200
#define TASK_RATE         30000 // 30 seconds


// Filescope Variables
static int ADCBuffer[ADC_BUFFER_LENGTH];
static int ADCBufferIndex;
static unsigned long AverageADCValue;
static int ADCTimerIndex;


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

  ADCTimerIndex = RegisterTimer();
  SetTimer(ADCTimerIndex, TASK_RATE);
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

  // Print Average ADC every TASK_RATE for testing
  if(IsTimerExpired(ADCTimerIndex))
  {
    SetTimer(ADCTimerIndex, TASK_RATE);
    Serial.print("Average ADC Value: ");
    Serial.println(AverageADCValue);
  }
}

int GetADCReading(void)
{
  return AverageADCValue;
}
