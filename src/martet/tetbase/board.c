
// the board where the gameplay happens and some related functions.
#include "board.h"

static char** board = NULL;

// board_create: creates the board represented as char array[20][10]
// space is empty other chars represent colors
void board_create(void){
    int i;
    char emptyrow[] = "          ";
    // allocate memory for board rows
    board = (char**) calloc(BOARD_HEIGHT, sizeof(char*));
    for (i = 0; i < BOARD_HEIGHT; ++i){
        // allocate memory for board columns
        board[i] = (char*) calloc(BOARD_WIDTH + 1, sizeof(char)); // one extra for '\0'
        // fill row with whitespace to init it to empty
        strcpy(board[i], emptyrow);
    }
}

// convert blocks coordinate to the corresponding coordinate on screen.
int convert_coordinate(int coordinate){
    return coordinate * BLOCK_SIZE;
}

// check_rows: calls delete_rows on full rows, returns number of rows deleted
int check_rows(int* score){
    int i;
    int rows_full = 0;
    for (i = BOARD_HEIGHT - 1; i > 0; --i){
        if (row_full(board[i])){
            rows_full = 1;
            delete_row(i);
            *score += 1;
        }
    }
    if (rows_full)
        check_rows(score);
    return 1;
}

bool row_full(char* row){
    int i;
    for (i = 0; i < BOARD_WIDTH; ++i){
        if (row[i] == ' ')
            return false;
        }
    return true;
}

void delete_row(int row){
    int i;
    char emptyrow[] = "          ";
    for (i = row; i > 0; --i)
        strcpy(board[i], board[i - 1]);
    strcpy(board[i], emptyrow);
    return;
}

// get_board_pos: returns char on board coordinates, used for collision
//                detection
char get_board_pos(int x, int y){
     if ((x < 0 ) || (x >= BOARD_WIDTH) || (y < 0 ) || (y >= BOARD_HEIGHT )){
         return 'X';
     }
    return board[y][x];
}

// get_board_line: returns string of chosen row
char* get_board_line(int y){
    if (y >= 0 && y <= BOARD_HEIGHT - 1)
        return board[y];
    else
        return NULL;
}

void place_tetromino(struct Tetromino* tetromino){
    int x;
    int y;
    x = tetromino->Block1.x + tetromino->position[0];
    y = tetromino->Block1.y + tetromino->position[1];
    board[y][x] = tetromino->color;
    x = tetromino->Block2.x + tetromino->position[0];
    y = tetromino->Block2.y + tetromino->position[1];
    board[y][x] = tetromino->color;
    x = tetromino->Block3.x + tetromino->position[0];
    y = tetromino->Block3.y + tetromino->position[1];
    board[y][x] = tetromino->color;
    x = tetromino->Block4.x + tetromino->position[0];
    y = tetromino->Block4.y + tetromino->position[1];
    board[y][x] = tetromino->color;
    tetromino->color = TETROMINO_DELETE;
}

void board_delete(void){
    int i;
    for (i = 0; i < BOARD_HEIGHT; ++i){
        // allocate memory for board columns
        free(board[i]);
    }
    free(board);
}