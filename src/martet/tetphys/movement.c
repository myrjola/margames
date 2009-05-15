
#include <stdio.h>
#include "tetphys.h"
#include "../tetbase/board.h"

void tetaction(char input, struct Tetromino* tetromino){
    switch (input){
        case (UP): tetrotate(tetromino); break;
        case (DOWN): tetfall(tetromino); break;
        case (LEFT):
        case (RIGHT): tetmove(input, tetromino); break;
        default: break;
    }
}

int tetmove(char direction, struct Tetromino* tetromino){
    int new_x = tetromino->position[0];
    int new_y = tetromino->position[1];
    switch (direction){
        case (UP):      new_y--; break;
        case (DOWN):    new_y++; break;
        case (LEFT):    new_x--; break;
        case (RIGHT):   new_x++; break;
        default: break;
    }
    // if all blocks can move, move tetromino
    if ( can_block_move(&tetromino->Block1, new_x, new_y))
        if ( can_block_move(&tetromino->Block2, new_x, new_y))
            if ( can_block_move(&tetromino->Block3, new_x, new_y))
                if ( can_block_move(&tetromino->Block4, new_x, new_y)){
                    tetromino->position[0] = new_x;
                    tetromino->position[1] = new_y;
                    return 1;
                }
    return 0;
}

can_block_move(struct Block* block, int x, int y){
    int new_x = block->x + x;
    int new_y = block->y + y;
    if ( get_board_pos(new_x, new_y) == ' ')
        return 1;
    return 0;
}

void tetfall(struct Tetromino* tetromino){
    while (tetmove('d', tetromino)) // drop the tetromino until collision
        ;
    return;
}
