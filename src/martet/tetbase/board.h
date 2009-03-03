// the board where the gameplay happens and some related functions.
#ifndef BOARD_H
#define BOARD_H

enum {BLOCK_SIZE = 32,
      BOARD_HEIGHT = 20,
      BOARD_WIDTH = 10};

// board_create: creates the board represented as char array[20][10]
// space is empty other chars represent colors
char** board_create(void);

// convert blocks coordinate to the corresponding coordinate on screen.
int convert_coordinate(int);

#endif // BOARD_H