// simple tile graphics engine for martet

#include <SDL/SDL.h>
#include "../../gamefunc/gfx/imagefunc.h"
#include "../tetbase/board.h"

#ifndef TILEGFX_H
#define TILEGFX_H

SDL_Surface* get_spritesheet(void);

// clear_board: fills board black
void clear_board(SDL_Surface*);

// draw_tetromino: draws the active_tetromino to the board
void draw_tetromino(SDL_Surface*, struct Tetromino*);

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface*);

// draw_block: draws a block to the board
void draw_block(SDL_Surface*, struct Block*, int, int, char);

#endif // TILEGFX_H