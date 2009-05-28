#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#ifndef IMAGEFUNC_H
#define IMAGEFUNC_H

SDL_Surface* load_image(const char*);

void draw_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);

#endif // IMAGEFUNC_H
