// simple graphics engine for martet just draws colored rectangles as blocks.

#include "fillrectgfx.h"

// clear_board: fills board black
void clear_board(SDL_Surface* boardsurf){
    SDL_FillRect(boardsurf, NULL, SDL_MapRGB(boardsurf, 0, 0, 0));
}

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface* boardsurf){
    int x = 0;
    int y = 0;
    char * currentrow = NULL;
    char   blockpos   = ' ';
    SDL_Rect blitrect;
    blitrect.w = 32;
    blitrect.h = 32;
    while (currentrow = get_board_line(y++)){ // iterate through the rows
        while (blockpos = currentrow[x++]){
            if (blockpos != ' '){ // if blockpos not empty
                blitrect.x = convert_coordinate(x);
                blitrect.y = convert_coordinate(y);
                SDL_FillRect(&boardsurf, &blitrect, SDL_MapRGB(boardsurf, 0, 0, 0));
            }
        }
    }
    return;
}