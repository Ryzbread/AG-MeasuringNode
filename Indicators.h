#ifndef INDICATORS_H
#define INDICATORS_H
// Includes

// Libraries

// DEFINES
#define PIN_ON_BOARD_LED  2
#define FR_0_5_HZ         1000
#define FR_0_25_HZ        2000
#define FR_ON             0


// Global Functions
void InitIndicator(void);
void ServiceIndicator(void);
void SetFlashRate(int FlashRate);


#endif // INDICATORS_H
