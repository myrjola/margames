
#include "tetbase.h"

// Tetrominoes as coordinates
const int TETROMINO_I[4][2] = {{0, 0},
                               {-1, 0},
                               {1, 0},
                               {2, 0}};

const int TETROMINO_J[4][2] = {{0, 0},
                               {1, 0},
                               {2, 0},
                               {0, -1}};

const int TETROMINO_L[4][2] = {{0, 0},
                               {1, 0},
                               {2, 0},
                               {0, 1}};

const int TETROMINO_O[4][2] = {{0, 0},
                               {-1, -1},
                               {-1, 0},
                               {0, -1}};

const int TETROMINO_S[4][2] = {{0, 0},
                               {-1, 0},
                               {0, -1},
                               {1, -1}};

const int TETROMINO_Z[4][2] = {{0, 0},
                               {1, 0},
                               {0, -1},
                               {-1, -1}};

const int TETROMINO_T[4][2] = {{0, 0},
                               {-1, 0},
                               {1, 0},
                               {0, -1}};

// tetcreate: creates a tetromino and passes the pointer to it
struct Tetromino* tetcreate(const int coordinates[4][2], char color){
    // allocate memory for tetromino
    struct Tetromino* tetromino;
    tetromino = (struct Tetromino*) malloc(sizeof(struct Tetromino));
    // create the tetromino
    tetromino->Block1.x = coordinates[0][0];
    tetromino->Block2.x = coordinates[1][0];
    tetromino->Block3.x = coordinates[2][0];
    tetromino->Block4.x = coordinates[3][0];
    tetromino->Block1.y = coordinates[0][1];
    tetromino->Block2.y = coordinates[1][1];
    tetromino->Block3.y = coordinates[2][1];
    tetromino->Block4.y = coordinates[3][1];
    tetromino->Block1.block_number = 1;
    tetromino->Block2.block_number = 2;
    tetromino->Block3.block_number = 3;
    tetromino->Block4.block_number = 4;
    tetromino->position[0] = 5; // width of board = 10
    tetromino->position[1] = 1; // 0 is up 20 is down

    // test if board free.
    if ( !tetmove('d', tetromino) )
        return NULL;
    
    tetromino->color = color;
    return tetromino;
}


struct Tetromino* tetcreaterand(void){
    struct Tetromino* tetromino;
    int roll = rand() % 7;
    if ( roll == 0 )
        tetromino = tetcreate(TETROMINO_I, '0');
    else if ( roll == 1 )
        tetromino = tetcreate(TETROMINO_J, '1');
    else if ( roll == 2 )
        tetromino = tetcreate(TETROMINO_L, '2');
    else if ( roll == 3 )
        tetromino = tetcreate(TETROMINO_O, '3');
    else if ( roll == 4 )
        tetromino = tetcreate(TETROMINO_S, '4');
    else if ( roll == 5 )
        tetromino = tetcreate(TETROMINO_T, '5');
    else if ( roll == 6 )
        tetromino = tetcreate(TETROMINO_Z, '6');
    else
        return NULL;
    return tetromino;
}
