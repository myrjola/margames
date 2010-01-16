#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#ifndef IMAGEFUNC_H
#define IMAGEFUNC_H

SDL_Surface* load_image(const char*);

void draw_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);

void clear_surface(SDL_Surface*, SDL_Rect*);

int draw_text(int, int, SDL_Surface*, const char*, Uint8, Uint8, Uint8);
    
#endif // IMAGEFUNC_H
