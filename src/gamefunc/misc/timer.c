
#include "timer.h"

struct Timer* timer_create(void){
    struct Timer* timer = malloc(sizeof(struct Timer));
    timer->running = 0;
    timer->time_from_start = 0;
    timer->time_passed_from_stop = 0;
    timer->time_stopped = 0;
    timer->alarm_interval = 0;
    timer->alarms = 0;
    return timer;
}

void timer_start(struct Timer* timer){
    unsigned int ticks = SDL_GetTicks();
    if ( !timer->running ){
        timer->running = 1;
        // if timer stopped before start
        if ( timer->time_passed_from_stop )
            timer->time_stopped += ticks - timer->time_passed_from_stop;
        // if timer started for the first time 
        else if ( !timer->time_from_start )
            timer->time_from_start = ticks;
    }
    return;
}

void timer_stop(struct Timer* timer){
    if ( timer->running ){
        timer->running = 0;
        timer->time_passed_from_stop = SDL_GetTicks();
    }
    return;
}

int timer_update(struct Timer* timer){
    unsigned int alarms_delta;
    if ( timer->alarm_interval ){
        unsigned int ticks = SDL_GetTicks();
        unsigned int alarms = ticks / timer->alarm_interval;
        alarms_delta = alarms - timer->alarms;
        timer->alarms += alarms_delta;
        return alarms_delta;
    }
}

void timer_change_alarm_interval(struct Timer* timer, unsigned int new_interval){
    unsigned int ticks = SDL_GetTicks();
    timer->alarm_interval = new_interval;
    timer->alarms = ticks / new_interval;
}
    
