// simple tile graphics engine for martet

#include <SDL/SDL.h>
#include "../gamefunc/gfx/imagefunc.h"
#include "../gamefunc/input/keyeventinput.h"
#include "../gamefunc/misc/miscutils.h"
#include "../gamefunc/misc/simplemenu.h"
#include "tetbase.h"

#ifndef TILEGFX_H
#define TILEGFX_H

SDL_Surface* get_spritesheet(bool transparent);

// clear_board: fills board black
void clear_board(SDL_Surface*);

// draw_tetromino: draws the active_tetromino to the board
void draw_tetromino(SDL_Surface*, Tetromino*);

// draw_tetromino: draws a ghost tetromino to the board where the
//                 active_tetromino would fall
void draw_ghost_tetromino(SDL_Surface*, Tetromino*);

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface*);

// draw_block: draws a block to the board
void draw_block(SDL_Surface*, struct Block*, int, int, char, int);

// pause_martet: pause loop
void pause_martet(SDL_Surface* screen, SDL_Surface* board);

// menu_martet: main menu loop
int menu_martet(SDL_Surface* screen, SDL_Surface* board,
                struct Menu* menu, int* score);

// ingame_menu_martet: ingame menu loop
int ingame_menu_martet(SDL_Surface* screen, SDL_Surface* board,
                       struct Menu* menu);

// update_status_bar: updates the next tetromino image and score
int update_status_bar(Tetromino* next_tetromino, SDL_Surface* screen,
                      int score);

#endif // TILEGFX_H