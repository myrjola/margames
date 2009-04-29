// simple graphics engine for martet just draws colored rectangles as blocks.

#include "fillrectgfx.h"


// clear_board: fills board black
void clear_board(SDL_Surface* boardsurf){
    SDL_FillRect(boardsurf, NULL, SDL_MapRGB(boardsurf->format, 0, 0, 0));
    return;
}

void draw_tetromino(SDL_Surface* boardsurf, struct Tetromino* tetromino){
    int x;
    int y;
    x = tetromino->position[0];
    y = tetromino->position[1];
    draw_block(boardsurf, &tetromino->Block1, x , y);
    draw_block(boardsurf, &tetromino->Block2, x , y);
    draw_block(boardsurf, &tetromino->Block3, x , y);
    draw_block(boardsurf, &tetromino->Block4, x , y);
    return;
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
    while (y < BOARD_HEIGHT){
        currentrow = get_board_line(y++);
        while (blockpos = currentrow[x++]){
            if (blockpos != ' '){ // if blockpos not empty
                printf("x:%d y:%d = '%c'\n", x-1, y-1, blockpos);
                blitrect.x = convert_coordinate(x);
                blitrect.y = convert_coordinate(y);
                SDL_FillRect(boardsurf, &blitrect, SDL_MapRGB(boardsurf->format, 255, 0, 0));
            }
        }
    }
    return;
}

void draw_block(SDL_Surface* boardsurf, struct Block* block, int x, int y){
    int newx;
    int newy;
    newx = block->x + x;
    newy = block->y + y;
    SDL_Rect blitrect;
    blitrect.w = 32;
    blitrect.h = 32;
    blitrect.x = convert_coordinate(newx);
    blitrect.y = convert_coordinate(newy);
    SDL_FillRect(boardsurf, &blitrect, SDL_MapRGB(boardsurf->format, 255,0,0));
    return;
}