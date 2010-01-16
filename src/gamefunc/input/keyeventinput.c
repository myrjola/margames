#include "keyeventinput.h"

int process_key_events(void* object, void (*action)(char, void*)){
    SDL_Event event;
    // Poll for events
    if (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN){
            // call the action function
            switch(event.key.keysym.sym){
                case SDLK_UP:    (*action)('u', object);break;
                case SDLK_DOWN:  (*action)('d', object);break;
                case SDLK_LEFT:  (*action)('l', object);break;
                case SDLK_RIGHT: (*action)('r', object);break;
                case SDLK_p:     return KEYEVENT_PAUSE;break;
                default: break;
            }
        }
        // if tried to exit
        else if (event.type == SDL_QUIT){
            // Quit
            return KEYEVENT_EXIT;
        }
    }
    return KEYEVENT_NOTHING;
}