// the board where the gameplay happens and some related functions.
#include "board.h"

// board_create: creates the board represented as char array[20][10]
// space is empty other chars represent colors
void board_create(void){
    int i;
    // allocate memory for board rows
    board = (char**) malloc(sizeof(char*) * BOARD_HEIGHT);
    i = 0;
    while (i < BOARD_HEIGHT){
        // allocate memory for board columns
        *(board + i) = (char*) malloc(sizeof(char) * BOARD_WIDTH + 1); // one extra for '\0'
        // fill row with whitespace to init it to empty
        *(board + i++) = "          ";
    }
}

// convert blocks coordinate to the corresponding coordinate on screen.
int convert_coordinate(int coordinate){
    return coordinate * BLOCK_SIZE;
}

// check_rows: calls delete_rows on full rows, returns number of rows deleted
int check_rows(void){
    int y = 0;              // y coordinate
    int x = 0;              // x coordinate
    int first_full_row;     // first found full row
    int rows_to_delete;
    while (y != 0){
        while (board[y][x++] != ' '){ // while block found on column
            if (x == BOARD_WIDTH){    // if row is full
                if (rows_to_delete == 0)
                    first_full_row   = y;
                rows_to_delete++;
            }

// delete_rows: deletes row or rows of blocks and calls drop_rows.
void delete_rows(int, int);

// drop_rows: drops rows above chosen row n steps down
void drop_rows(int, int);

// get_board_pos: returns char on board coordinates
char get_board_pos(int, int);
