
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
    // if all blocks can move, move tetromino. Using recursion just for
    // practice
    if (blockmove(direction, tetromino, 1)) // if tetromino could move
        return 1;
    else
        return 0;
}

// blockmove: move block left for 'l', right for 'r'
//            and down for 'd' return 1 if succesful else 0
int blockmove(char direction, struct Tetromino* tetromino, int block_number){
    struct Block* block;
    switch (block_number){
        case (1): block = &tetromino->Block1; break;
        case (2): block = &tetromino->Block2; break;
        case (3): block = &tetromino->Block3; break;
        case (4): block = &tetromino->Block4; break;
        default: break;
    }
    int new_x = block->x;
    int new_y = block->y;
    // calculate the new position
    switch (direction){
        case (UP):      new_y--; break;
        case (DOWN):    new_y++; break;
        case (LEFT):    new_x--; break;
        case (RIGHT):   new_x++; break;
        default: break;
    }
    if (block->block_number == 4){               // if last block
        if (get_board_pos(new_x, new_y) == ' '){ // if position free
            block->x = new_x;                        // move block and return success
            block->y = new_y;
            return 1;
        }
        else {
            return 0; // else return failure
        }
    }
    else { // if not last block
        if (blockmove(direction, tetromino, block_number + 1)){ // test if move possible with next block
            if (get_board_pos(new_x, new_y) == ' '){     // if position free
                block->x = new_x;                        // move block and return success
                block->y = new_y;
                return 1;
            }
        }
        else {
            printf("couldn't move\n");
            return 0; // else return failure
        }
    }
}

void tetfall(struct Tetromino* tetromino){
    while (tetmove('d', tetromino)) // drop the tetromino until collision
        ;
    return;
}
