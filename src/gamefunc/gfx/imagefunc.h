#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface* load_image(const char* filename);

void draw_surface(int x, int y, SDL_Surface* source, SDL_Surface* target);