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

int input_text(char* string, int bufsize) {
    SDL_Event event;
    Uint16 unicode;
    int i = 0;
    while (string[i] != 0) // goto end of string
        i++;
    if (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN){
            unicode = event.key.keysym.unicode;
            // enter should end input
            if (event.key.keysym.sym == SDLK_RETURN) {
                return KEYEVENT_EOL;
            }
            // if backspace delete last character
            else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                if (i != 0) { // if string not empty
                    string[i - 1] = 0;
                }
            }
            // pressing esc garbles the string
            else if (event.key.keysym.sym == SDLK_ESCAPE) {
                return KEYEVENT_NOTHING;
            }
            // else append the unicode to the end
            else {
                // Out of space or wrong key
                if (i >= bufsize - 2 || unicode == 0) {
                    return KEYEVENT_NOTHING;
                }
                string[i] = (char) unicode;
                string[i + 1] = 0;
            }
        }
        else if (event.type == SDL_QUIT){
            // Quit
            return KEYEVENT_EXIT;
        }
    }
    return KEYEVENT_NOTHING;
}
             
    
    
    