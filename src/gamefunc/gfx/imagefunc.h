#include <stdlib.h>
#include <stdbool.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#ifndef IMAGEFUNC_H
#define IMAGEFUNC_H

// create_surface - Returns black surface optimized to display format.
SDL_Surface* create_surface(int w, int h);

// load_image - Loads everything SDL_image knows.
SDL_Surface* load_image(const char*);

// draw_surface - simple surface draw function. If clip is NULL the whole
// surface will be drawn.
void draw_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);

// draw_surface_centered - centered surface draw function
void draw_surface_centered(SDL_Surface* source, SDL_Surface* target);

// clear_surface - fills rect in surface black
void clear_surface(SDL_Surface*, SDL_Rect*);

// draw_text - simple text rendering. If surf == NULL return text_surface
SDL_Surface* draw_text(int x, int y, SDL_Surface* surf, char* text,
                       Uint8 r, Uint8 b, Uint8 g);
                       
SDL_Surface* draw_text_multiline(int x, int y, SDL_Surface* surf, char* text,
                                 Uint8 r, Uint8 b, Uint8 g);

#endif // IMAGEFUNC_H
