#ifndef TIME_H
#define TIME_H
// Includes

// Libraries


// Global Functions
void InitTime(void);
bool ServiceTime(void);
int RegisterTimer(void);
int SetTimer(int TimerID, unsigned long Duration);
int ClearTimer(int TimerID);
bool IsTimerRunning(int TimerID);
bool IsTimerExpired(int TimerID);


#endif // TIME_H
