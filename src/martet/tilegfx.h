// simple tile graphics engine for martet

#include <SDL/SDL.h>
#include "../gamefunc/gfx/imagefunc.h"
#include "tetbase.h"

#ifndef TILEGFX_H
#define TILEGFX_H

SDL_Surface* get_spritesheet(int);

// clear_board: fills board black
void clear_board(SDL_Surface*);

// draw_tetromino: draws the active_tetromino to the board
void draw_tetromino(SDL_Surface*, struct Tetromino*);

// draw_tetromino: draws a ghost tetromino to the board where the
//                 active_tetromino would fall
void draw_ghost_tetromino(SDL_Surface*, struct Tetromino*);

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface*);

// draw_block: draws a block to the board
void draw_block(SDL_Surface*, struct Block*, int, int, char, int);

#endif // TILEGFX_H