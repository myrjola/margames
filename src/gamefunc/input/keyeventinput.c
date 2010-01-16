#include "keyeventinput.h"

int process_key_events(void* object, int (*action)(char, void*)){
    SDL_Event event;
    // Poll for events
    if (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN){
            // call the action function
            switch(event.key.keysym.sym){
                case SDLK_UP:     return (*action)('u', object);break;
                case SDLK_DOWN:   return (*action)('d', object);break;
                case SDLK_LEFT:   return (*action)('l', object);break;
                case SDLK_RIGHT:  return (*action)('r', object);break;
                case SDLK_RETURN: return (*action)('\n', object);break;
                case SDLK_p:      return KEYEVENT_PAUSE;break;
                case SDLK_ESCAPE: return KEYEVENT_MENU;break;
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