#include <stdbool.h>
#include "tetromino.h"

#ifndef TETPHYS_H
#define TETPHYS_H

enum {UP    = 'u',
      DOWN  = 'd',
      LEFT  = 'l',
      RIGHT = 'r'};

// tetaction: actions for tetrominoes based on input.
void tetaction(char, void*);

// tetmove: move tetromino left for 'l', right for 'r'
//          and down for 'd' return 1 if succesful else 0
int tetmove(char, struct Tetromino*);

int can_block_move(struct Block*, int, int);

// tetfall: let the tetromino fall down until collision detected
void tetfall(struct Tetromino*);


// tetrotate: rotates the tetromino 90 degrees clockwise
void tetrotate(struct Tetromino*);

// pointrotate: rotates point in 90 degrees clockwise
//              relative to origo. Used for tetromino
//              blocks.
int* pointrotate(struct Block*);

// if_no_collision(board, x, y): if no block at coordinate return true
bool if_no_collision(char**, int, int);

#endif // TETPHYS_H
