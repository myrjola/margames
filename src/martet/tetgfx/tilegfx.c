#include "tilegfx.h"

static SDL_Surface* spritesheet = NULL;

SDL_Surface* get_spritesheet(void){
    if ( spritesheet )
        return spritesheet;
    spritesheet = load_image("data/tetblocks.png");
    return spritesheet;
}

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
    draw_block(boardsurf, &tetromino->Block1, x , y, tetromino->color);
    draw_block(boardsurf, &tetromino->Block2, x , y, tetromino->color);
    draw_block(boardsurf, &tetromino->Block3, x , y, tetromino->color);
    draw_block(boardsurf, &tetromino->Block4, x , y, tetromino->color);
    return;
}

// draw_board: draws the blocks to the board
void draw_board(SDL_Surface* boardsurf){
    int x = 0;
    int y = 0;
    char blockpos = ' ';
    while (y <= BOARD_HEIGHT){
        while (x < BOARD_WIDTH){
            blockpos = get_board_pos(x, y);
            if (blockpos != ' '){ // if blockpos not empty
                draw_block(boardsurf, NULL, x,
                            y, blockpos);
            }
            x++;
        }
        x = 0;
        y++;
    }
    return;
}

void draw_block(SDL_Surface* boardsurf, struct Block* block, int x, int y, char color){
    SDL_Surface* blocksprites = get_spritesheet();
    int newx = x;
    int newy = y;
    //
    int which_color = (int) (color - '0');
    if ( block ){
        newx += block->x;
        newy += block->y;
    }
    newx = convert_coordinate(newx);
    newy = convert_coordinate(newy);
    SDL_Rect cliprect;
    cliprect.w = 32;
    cliprect.h = 32;
    cliprect.x = 32 * which_color;
    cliprect.y = 0;
    draw_surface(newx, newy, blocksprites, boardsurf, &cliprect);
    return;
}