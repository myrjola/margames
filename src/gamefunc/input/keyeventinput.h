#include "SDL/SDL.h"

#ifndef KEYEVENTINPUT_H
#define KEYEVENTINPUT_H

enum {KEYEVENT_NOTHING, KEYEVENT_EXIT,
      KEYEVENT_PAUSE, KEYEVENT_MENU};

// process_key_events: input using SDL_KEY_UP
// and SDL_KEY_DOWN in case of event a pointer
// to a function is dereferenced and passed
// the key pressed and a pointer to usually
// an object controlled by input. returns 1
// if player tries to quit
int process_key_events(void*, void (*action)(char, void*));

#endif // KEYEVENTINPUT_H