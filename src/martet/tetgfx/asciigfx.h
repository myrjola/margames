// asciigfx functions useful for testing and debugging from the command line
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../tetphys/tetromino.h"

#ifndef ASCIIGFX_H
#define ASCIIGFX_H

// blocks2string: makes the strings for draw_tetromino_ascii's use.
char** blocks2strings(struct Tetromino*);

// draw_tetromino_ascii: draws tetromino's blocks as 'O', empty space
//                       represented by whitespace.
void draw_tetromino_ascii(struct Tetromino*);

#endif