#include <stdlib.h>
#include <stdio.h>

#include "SDL/SDL.h"

#include "gamefunc/imagefunc.h"


int main(int argc, char** argv){
    SDL_Surface* screen     = NULL;
    SDL_Surface* background = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    printf("SDL initialized\n");
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    background = load_image("data/kaboom.png");
    if (background == NULL){
        printf("image kaboom.png not found");
        return 1;
    }
    draw_surface(0, 0, background, screen);
    SDL_Flip(screen);
    SDL_Delay(5000);
    SDL_Quit();
    return 0;
}
