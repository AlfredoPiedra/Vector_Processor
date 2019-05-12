#include "clock.h"

unsigned char Clock::clock = 0;

Clock::Clock(){

    pthread_t clock_tid;

    pthread_create(&clock_tid,0,ClockThread,0);

    pthread_detach(clock_tid);

}

void* Clock::ClockThread(void *ptr){

    while(1){

        usleep(10000);
        clock = !clock;
        std::cout << "Hola desde el clock" << (int)clock << std::endl;
    }

    pthread_exit(ptr);
}

void Clock::StartClock(){


}


void Clock::StopClock(){


}
