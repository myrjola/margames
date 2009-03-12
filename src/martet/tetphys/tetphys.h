#include <stdbool.h>
#include "tetromino.h"

#ifndef TETPHYS_H
#define TETPHYS_H

enum {UP    = 'u',
      DOWN  = 'd',
      LEFT  = 'l',
      RIGHT = 'r'};

// tetaction: actions for tetrominoes based on input.
void tetaction(char, struct Tetromino*);

// tetmove: move tetrominoe left for 'l', right for 'r'
//          and down for 'd' return 1 if succesful else 0
void tetmove(char, struct Tetromino*);

// blockmove: move block in tetromino left for 'l', right for 'r'
//            and down for 'd' return 1 if succesful else 0
int blockmove(char, struct Tetromino*, int);

// tetfall: let the tetromino fall down until collision detected
void tetfall(struct Tetromino*);

// if_no_collision(board, x, y): if no block at coordinate return true
bool if_no_collision(char**, int, int);

#endif // TETPHYS_H
