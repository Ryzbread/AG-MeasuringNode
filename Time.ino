// Includes
#include "Time.h"


// DEFINES
#define TICK_DURATION       5 // milliseconds
#define NUMBER_OF_TIMERS    10

// Filescope Variables
static unsigned long currentTime;
static unsigned long lastTickTime;
static bool Tick;

static int TimerIndex;
static unsigned long Timers[NUMBER_OF_TIMERS];
static int OneSecondTimer;

void InitTime(void)
{
    currentTime = millis();
    Tick = false;
    TimerIndex = 0;
    OneSecondTimer = RegisterTimer();
    SetTimer(OneSecondTimer, 1000);
}

bool ServiceTime(void)
{
    currentTime = millis();
    Tick = false;

    if((lastTickTime + TICK_DURATION) <= currentTime)
    {
        Tick = true;
        lastTickTime = currentTime;

    }

    if(Tick)
    {
        // Perform Tick Actions
        ServiceTimers();
    }

    // Print current time in 1 second intervals for testing.
    if(IsTimerExpired(OneSecondTimer))
    {
        SetTimer(OneSecondTimer, 1000);
        Serial.print("One Second Timer: ");
        Serial.println(currentTime);   
    }

    return Tick;
}

static void ServiceTimers(void)
{
    int Index;

    // Tick down all timers
    for(Index = 0; Index < TimerIndex; Index++)
    {
        if(IsTimerRunning(Index))
        {
            Timers[Index] -= 1;
        }
    }
}

int RegisterTimer(void)
{
    int TimerID;
    
    if(TimerIndex < NUMBER_OF_TIMERS)
    {
        TimerID = TimerIndex++;
        // Clear Timer
        Timers[TimerID] = 0;
    }
    else
    {
        // Too many timers have been registered. Return error.
        TimerID = -1;
    }


    return TimerID;
}

int SetTimer(int TimerID, unsigned long Duration)
{
    int Status;

    if(TimerID < TimerIndex)
    {
        Timers[TimerID] = (Duration / TICK_DURATION);
        Status = 1;
    }
    else
    {
        // Attempting to set an unregistered Timer. Return error.
        Status = -1;
    }

    return Status;
}

int ClearTimer(int TimerID)
{
    int Status;

    if(TimerID < TimerIndex)
    {
        Timers[TimerID] = 0;
        Status = 1;
    }
    else
    {
        // Attempting to clear an unregistered Timer. Return error.
        Status = -1;
    }

    return Status;
}

bool IsTimerRunning(int TimerID)
{
    // Assume false if invalid ID is passed.
    bool IsRunning = false;

    if(TimerID < TimerIndex)
    {
        IsRunning = Timers[TimerID] > 0;
    }

    return IsRunning;
}

bool IsTimerExpired(int TimerID)
{
    // Assume false if invalid ID is passed.
    bool IsExpired = false;

    if(TimerID < TimerIndex)
    {
        IsExpired = Timers[TimerID] == 0;
    }

    return IsExpired;
}
