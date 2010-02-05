#include "SDL/SDL.h"

#ifndef KEYEVENTINPUT_H
#define KEYEVENTINPUT_H

enum {KEYEVENT_NOTHING, KEYEVENT_EXIT,
      KEYEVENT_PAUSE, KEYEVENT_MENU,
      KEYEVENT_EOL, KEYEVENT_ANY_OTHER_KEY};

// process_key_events: Input using SDL_KEY_UP
// and SDL_KEY_DOWN in case of event a pointer
// to a function is referenced and passed
// the key pressed and a pointer to usually
// an object controlled by input. Returns 1
// if player tries to quit.
int process_key_events(void*, int (*action)(char, void*));

// input_text: Rudimentary text input. Modifies the unicode string according
// to the keypresses. Checks for buffer overflow according to parameter bufsize.
// Returns KEYEVENT_EXIT if user tries to quit and KEYEVENT_EOL when return is
// pressed.
int input_text(char* string, int bufsize);

#endif // KEYEVENTINPUT_H