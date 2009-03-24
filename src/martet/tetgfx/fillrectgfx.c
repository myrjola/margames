// simple graphics engine for martet just draws colored rectangles as blocks.

#include "fillrectgfx.h"

// clear_board: fills board black
void clear_board(SDL_Surface* boardsurf){
    SDL_FillRect(boardsurf, NULL, SDL_MapRGB(board, 0, 0, 0));
}

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface* boardsurf){
    

