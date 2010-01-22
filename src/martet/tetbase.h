#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#ifndef TETBASE_H_
#define TETBASE_H_


enum {BLOCK_SIZE = 32,
      BOARD_HEIGHT = 20,
      BOARD_WIDTH = 10,
      UP    = 'u',
      DOWN  = 'd',
      LEFT  = 'l',
      RIGHT = 'r',
      TETROMINO_DELETE = 'x'};

// Colors of tetris blocks used by the block drawing function
enum colors {RED = 0, YELLOW, GREEN, BLUE, PURPLE, BROWN, GREY};

// Tetrominoes as coordinates
const int TETROMINO_I[4][2];
const int TETROMINO_J[4][2];
const int TETROMINO_L[4][2];
const int TETROMINO_O[4][2];
const int TETROMINO_S[4][2];
const int TETROMINO_Z[4][2];
const int TETROMINO_T[4][2];

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
// board_create: creates the board represented as char array[20][10 + 1]
// space is empty other chars represent colors

void board_create(void);

// convert_coordinate: convert blocks coordinate to the corresponding coordinate
//                     on screen.
int convert_coordinate(int);

// check_rows: calls delete_rows if full row/-s of blocks found returns no.
//              of rows deleted
int check_rows(int*);

bool row_full(char*);

// delete_row: drops the rows above
void delete_row(int);

// get_board_pos: returns char on board coordinates
char get_board_pos(int, int);

// get_board_line: returns string of chosen row
char* get_board_line(int);

// place_tetromino: places tetromino on board and spawns a new one
void place_tetromino(struct Tetromino*);

void board_delete(void);

// tetaction: actions for tetrominoes based on input.
int tetaction(char, void*);

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

// tetcreate: creates a tetromino and passes the pointer to it
struct Tetromino* tetcreate(const int coordinates[4][2], char);

struct Tetromino* tetcreaterand(void);

#endif // TETBASE_H_