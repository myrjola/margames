#include <stdlib.h>
#include <math.h>

#ifndef TETROMINO_H
#define TETROMINO_H

// Tetrominoes as coordinates
const int TETROMINO_I[4][2];
const int TETROMINO_J[4][2];
const int TETROMINO_L[4][2];
const int TETROMINO_O[4][2];
const int TETROMINO_S[4][2];
const int TETROMINO_Z[4][2];
const int TETROMINO_T[4][2];

// Colors of tetris blocks used by the block drawing function
enum colors;

struct Block{
    int x;
    int y;
    int block_number; // tetromino has 4 blocks
};

struct Tetromino{
    struct Block Block1;
    struct Block Block2;
    struct Block Block3;
    struct Block Block4;
    // the coordinates of Block1 on the board
    int position[2];
    char color;
};

// tetcreate: creates a tetromino and passes the pointer to it
struct Tetromino* tetcreate(const int coordinates[4][2]);

// tetrotate: rotates the tetromino 90 degrees clockwise
void tetrotate(struct Tetromino*);

// pointrotate: rotates point in 90 degrees clockwise
//              relative to origo. Used for tetromino
//              blocks.
void pointrotate(struct Block*);

struct Tetromino* tetcreaterand(void);

#endif /* TETROMINO_H */
