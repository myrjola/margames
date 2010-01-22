#include "tetbase.h"

int tetaction(char input, void* tetromino){
    switch (input){
        case (UP): tetrotate(tetromino); break;
        case (DOWN): tetfall(tetromino); break;
        case (LEFT):
        case (RIGHT): tetmove(input, tetromino); break;
        default: break;
    }
    return 0;
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
    place_tetromino(tetromino);
    return;
}

// tetrotate: rotates the tetromino 90 degrees clockwise
void tetrotate(struct Tetromino* tetromino){
    // Block1 always as pivot point
    int block2pos[2];
    int block3pos[2];
    int block4pos[2];
    int* block2relpos = pointrotate(&(tetromino->Block2));
    int* block3relpos = pointrotate(&(tetromino->Block3));
    int* block4relpos = pointrotate(&(tetromino->Block4));
    block2pos[0] = block2relpos[0] + tetromino->position[0];
    block2pos[1] = block2relpos[1] + tetromino->position[1];
    block3pos[0] = block3relpos[0] + tetromino->position[0];
    block3pos[1] = block3relpos[1] + tetromino->position[1];
    block4pos[0] = block4relpos[0] + tetromino->position[0];
    block4pos[1] = block4relpos[1] + tetromino->position[1];
    // rotate tetromino if enough room.
    if ( get_board_pos(block2pos[0], block2pos[1]) == ' ')
        if ( get_board_pos(block3pos[0], block3pos[1]) == ' ')
            if ( get_board_pos(block4pos[0], block4pos[1]) == ' '){
                tetromino->Block2.x = block2relpos[0];
                tetromino->Block2.y = block2relpos[1];
                free(block2relpos);
                tetromino->Block3.x = block3relpos[0];
                tetromino->Block3.y = block3relpos[1];
                free(block3relpos);
                tetromino->Block4.x = block4relpos[0];
                tetromino->Block4.y = block4relpos[1];
                free(block4relpos);
            }
     return;
}

// pointrotate: rotates point in 90 degrees clockwise
//              relative to origo. Used for tetromino
//              blocks.
int* pointrotate(struct Block* block){
    int* newpos= calloc(2, sizeof(int));
    // cast the coordinates to doubles
    // needed by the math functions
    double x = (double) block->x;
    double y = (double) block->y;
    // distance to origo
    double distance = sqrt((x*x + y*y));
    // calculate the initial direction in radians
    double angle;
    if (x != 0){
        angle = acos(x / distance);
        // angle range 0 , 180 if y not checked
        if (y < 0)
            angle = -angle;
    }
    else
        angle = asin(y / distance);

    angle += 1.57;

    // rotation using trigonometry
    x = distance * cos(angle);
    y = distance * sin(angle);
    // approximate the doubles to integers
    newpos[0] = (int) (x >= 0) ? (x + 0.5) : (x - 0.5);
    newpos[1] = (int) (y >= 0) ? (y + 0.5) : (y - 0.5);
    return newpos;
}
