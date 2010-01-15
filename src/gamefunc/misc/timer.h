// timer functions needed in various games
#include <stdlib.h>
#include "SDL/SDL.h"

#ifndef TIMER_H_
#define TIMER_H_

struct Timer{
    unsigned int running;
    // time passed from program start to timer start in milliseconds
    unsigned int time_from_start;
    unsigned int time_passed_from_stop;
    unsigned int time_stopped;
    unsigned int alarm_interval;
    unsigned int alarms;
};

struct Timer* create_timer(void);

void timer_start(struct Timer*);

void timer_stop(struct Timer*);

// update_timer: returns number of alarms since last update
int timer_update(struct Timer*);

void timer_change_alarm_interval(struct Timer*, unsigned int);

#endif