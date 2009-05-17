
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
int check_rows(void){
    int y = 0;              // y coordinate
    int first_full_row;     // first found full row
    int rows_to_delete = 0;
    while (y < BOARD_HEIGHT){
        if (row_full(board[y])){
            if (rows_to_delete == 0){
                first_full_row = y;
            }
            rows_to_delete++;
            y++;
        }
        else if (rows_to_delete == 0){ // none full rows found continue search
            y++;
        }
        else if (rows_to_delete > 0){   // all full rows found, now delete them
            delete_rows(y, rows_to_delete);
            return rows_to_delete;
        }
    }
}

bool row_full(char* row){
    int i;
    for (i = 0; i < BOARD_WIDTH; ++i){
        if (row[i] == ' ')
            return false;
        }
    return true;
}

// delete_rows: deletes number of rows starting from startrow.
void delete_rows(int startrow, int numrows){
    int x; // x coordinate
    int currentrow = startrow;
    int first_row_to_drop = startrow - 1;
    int numrowsleft = numrows;
    while (numrowsleft--){ // while still rows to delete left
        x = 0; // start from beginning of row
        clear_row(board[currentrow]);
        currentrow++;
    }
    drop_rows(first_row_to_drop, numrows); // drop the rows above
    return;
}

void clear_row(char* row){
    int x = 0; // x coordinate
    while (x < BOARD_HEIGHT){
        row[x++] = ' ';
    }
    return;
}

// drop_rows: drops rows above chosen row n steps down
void drop_rows(int startrow, int numrows){
    int currentrow = startrow;
    char* source; // which row to drop
    char* dest;   // where to drop
    while (currentrow > 0){ // iterate all the way to the top
        source = board[currentrow];
        dest = board[currentrow + numrows];
        dest = strcpy(dest, source);
        clear_row(source); // clear old row
        currentrow--;
    }
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

void drop_tetromino(struct Tetromino* tetromino){
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
}
