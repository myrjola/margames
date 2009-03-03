#include "asciigfx.h"

// blocks2strings: makes the strings for draw_tetromino_ascii's use
char** blocks2strings(struct Tetromino* tetromino){
    int i;
    // Color used for the block drawing function
    char color = (char) tetromino->color;
    // string represents 5 coordinates: range(-2, 2)
    char line1[] = "     "; // y = -2
    char line2[] = "     "; // y = -1 and so on...
    char line3[] = "     ";
    char line4[] = "     ";
    char line5[] = "     ";
    line3[2] = color; // Block1 allways in the middle
    // then the ascii art practically an array of 5 strings
    //char** lines = (char*) calloc(5, sizeof(char) * 6);
    char** lines = (char**) malloc(sizeof(char*) * 5);
    i = 0;
    while (i < 5)
        *(lines + i++) = (char*) malloc(sizeof(char) * 6); // one extra for '\0'

    // just write an 'O' on coordinates of block
    // remember that lineX[2] : x = 0
    switch (tetromino->Block2.y){
        case (-2): line1[tetromino->Block2.x + 2] = color;
        break;
        case (-1): line2[tetromino->Block2.x + 2] = color;
        break;
        case (0):  line3[tetromino->Block2.x + 2] = color;
        break;
        case (1):  line4[tetromino->Block2.x + 2] = color;
        break;
        case (2):  line5[tetromino->Block2.x + 2] = color;
        break;
        default: break;
    }
    switch (tetromino->Block3.y){
        case (-2): line1[tetromino->Block3.x + 2] = color;
        break;
        case (-1): line2[tetromino->Block3.x + 2] = color;
        break;
        case (0):  line3[tetromino->Block3.x + 2] = color;
        break;
        case (1):  line4[tetromino->Block3.x + 2] = color;
        break;
        case (2):  line5[tetromino->Block3.x + 2] = color;
        break;
        default: break;
    }
    switch (tetromino->Block4.y){
        case (-2): line1[tetromino->Block4.x + 2] = color;
        break;
        case (-1): line2[tetromino->Block4.x + 2] = color;
        break;
        case (0):  line3[tetromino->Block4.x + 2] = color;
        break;
        case (1):  line4[tetromino->Block4.x + 2] = color;
        break;
        case (2):  line5[tetromino->Block4.x + 2] = color;
        break;
        default: break;
    }

    strcpy(*(lines + 0), line1);
    strcpy(*(lines + 1), line2);
    strcpy(*(lines + 2), line3);
    strcpy(*(lines + 3), line4);
    strcpy(*(lines + 4), line5);
    return lines;
}
// draw_tetromino_ascii: draws tetromino's blocks as 'O', empty space
//                       represented by whitespace.
void draw_tetromino_ascii(struct Tetromino* tetromino){
    int i = 0;
    char** lines; // the ascii art to be drawn
    lines = blocks2strings(tetromino);
    while (i < 5){
        printf(*(lines + i++));
        printf("\n");
    }
    return;
}