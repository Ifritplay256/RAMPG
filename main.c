#include "stdio.h"
#include "Main/Console.h"
#include "Main/3drender.h"

#ifndef TIME_WRAPPER_H
#define TIME_WRAPPER_H

#ifdef _WIN32
    #include <windows.h>
    void sleep_ms(int ms) {
        Sleep(ms);
    }
#else
    #include <time.h>
    
    void sleep_ms(int ms) {
        struct timespec ts;
        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000;
        nanosleep(&ts, NULL);
    }
#endif

#endif

int main(){
    render_console(); 
    int tick = 0;   
    while (1){
        if (tick > 0){
            set_char(1, tick-1, ' ', 100, 100, 100);
        }
        set_char(1, tick, '=', 255, 100, 100);
        update_console();
        sleep_ms(1000);
        tick++;
    }

    return 0;
}