// the board where the gameplay happens and the functions needed to manipulate
// it. Declared the board variable static so that functions outside board.c
// can't directly mess with it.
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../tetphys/tetromino.h"

#ifndef BOARD_H
#define BOARD_H

enum {BLOCK_SIZE = 32,
      BOARD_HEIGHT = 20,
      BOARD_WIDTH = 10};

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

#endif // BOARD_H
