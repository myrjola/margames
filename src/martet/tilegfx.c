#include "tilegfx.h"


SDL_Surface* get_spritesheet(int transparent){
    static SDL_Surface* spritesheet = NULL;
    static SDL_Surface* spritesheet_transparent = NULL;
    if ( spritesheet ) {
        if (transparent)
            return spritesheet_transparent;
        else if (!transparent)
            return spritesheet;
    }
    spritesheet = load_image("../data/tetblocks.png");
    spritesheet_transparent = load_image("../data/tetblocks.png");
    SDL_SetAlpha(spritesheet_transparent, SDL_SRCALPHA, 100);
    return get_spritesheet(transparent);
}

void draw_tetromino(SDL_Surface* boardsurf, struct Tetromino* tetromino){
    int x;
    int y;
    x = tetromino->position[0];
    y = tetromino->position[1];
    draw_block(boardsurf, &tetromino->Block1, x , y, tetromino->color, 0);
    draw_block(boardsurf, &tetromino->Block2, x , y, tetromino->color, 0);
    draw_block(boardsurf, &tetromino->Block3, x , y, tetromino->color, 0);
    draw_block(boardsurf, &tetromino->Block4, x , y, tetromino->color, 0);
    return;
}

void draw_ghost_tetromino(SDL_Surface * boardsurf, struct Tetromino* tetromino) {
    int x;
    int y;
    struct Tetromino ghost = *tetromino;
    while (tetmove('d', &ghost)) // drop the tetromino until collision
        ;
    x = ghost.position[0];
    y = ghost.position[1];
    draw_block(boardsurf, &ghost.Block1, x , y, ghost.color, 1);
    draw_block(boardsurf, &ghost.Block2, x , y, ghost.color, 1);
    draw_block(boardsurf, &ghost.Block3, x , y, ghost.color, 1);
    draw_block(boardsurf, &ghost.Block4, x , y, ghost.color, 1);
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
                            y, blockpos, 0);
            }
            x++;
        }
        x = 0;
        y++;
    }
    return;
}

void draw_block(SDL_Surface* boardsurf, struct Block* block, int x, int y,
                char color, int transparent){
    SDL_Surface* blocksprites;
    if (transparent)
        blocksprites = get_spritesheet(1);
    else if (!transparent)
        blocksprites = get_spritesheet(0);
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