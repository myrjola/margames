// simple graphics engine for martet just draws colored rectangles as blocks.

#include <SDL/SDL.h>

#include "../tetbase/board.h"

#ifndef FILLRECTGFX_H
#define FILLRECTGFX_H

// clear_board: fills board black
void clear_board(SDL_Surface*);

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface*);

#endif // FILLRECTGFX_H