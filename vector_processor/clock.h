#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <pthread.h>
#include <unistd.h>

class Clock{

private:

    static void* ClockThread(void *ptr);

public:

    static unsigned char clock;

    Clock();

    void StartClock();
    void StopClock();
};

#endif // CLOCK_H
