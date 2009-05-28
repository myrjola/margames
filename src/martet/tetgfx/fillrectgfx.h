// simple graphics engine for martet just draws colored rectangles as blocks.

#include <SDL/SDL.h>

#include "../tetbase/board.h"
#include "../tetphys/tetromino.h"

#ifndef FILLRECTGFX_H
#define FILLRECTGFX_H

// clear_board: fills board black
void clear_board(SDL_Surface*);

// draw_tetromino: draws the active_tetromino to the board
void draw_tetromino(SDL_Surface*, struct Tetromino*);

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface*);

// draw_block: draws a block to the board
void draw_block(SDL_Surface*, struct Block*, int x, int y);

#endif // FILLRECTGFX_H