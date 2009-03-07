// the board where the gameplay happens and some related functions.
#include "board.h"

// board_create: creates the board represented as char array[20][10]
// space is empty other chars represent colors
char** board_create(void){
    int i;
    // allocate memory for board rows
    char** board = (char**) malloc(sizeof(char*) * BOARD_HEIGHT);
    i = 0;
    while (i < BOARD_HEIGHT){
        // allocate memory for board columns
        *(board + i) = (char*) malloc(sizeof(char) * BOARD_WIDTH + 1); // one extra for '\0'
        // fill row with whitespace to init it to empty
        *(board + i++) = "          ";
    }
    return board;
}

// convert blocks coordinate to the corresponding coordinate on screen.
int convert_coordinate(int coordinate){
    return coordinate * BLOCK_SIZE;
}
