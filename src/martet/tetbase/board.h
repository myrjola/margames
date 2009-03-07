// the board where the gameplay happens and the functions needed to manipulate
// it. Declared the board variable static so that functions outside board.c
// can't directly mess with it.

#ifndef BOARD_H
#define BOARD_H

enum {BLOCK_SIZE = 32,
      BOARD_HEIGHT = 20,
      BOARD_WIDTH = 10};

static char** board = NULL;

// board_create: creates the board represented as char array[20][10 + 1]
// space is empty other chars represent colors

char** board_create(void);

// convert_coordinate: convert blocks coordinate to the corresponding coordinate on screen.
int convert_coordinate(int);

// check_lines: calls delete_lines if full line/-s of blocks found

// delete_lines: deletes line or lines of blocks and calls drop_lines.

// drop_lines: drops lines above chosen line n steps down

// get_board_pos:

#endif // BOARD_H
