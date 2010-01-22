
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

// check_bag: check if a specific shape is taken from the bag
int check_bag(int roll, int bag_length, int bag[]) {
    bool shape_taken = false;
    int i;
    for (i = 0; i < bag_length; i++) {
        if ( roll == bag[i] ) { // shape already taken
            shape_taken = true;
            if ( roll <= 4 ) { // if roll in the lower half
                roll = rand() % 4 + 3; // choose one from the upper half
                break;
            }
            else {
                roll = rand() % 3;
                break;
            }
        }
    }
    if (shape_taken) {
        return check_bag(roll, bag_length, bag);
    }
    return roll;
}
    
    

struct Tetromino* tetcreaterand(void){
    struct Tetromino* tetromino;
    static int* bag = NULL;
    if (bag == NULL) {
        bag = (int*) calloc(7, sizeof(int));
    }
    static int bag_length = 7;
    int i;
    int roll = rand() % 7;
    if (bag_length == 7) { // bag full
        for (i = 0; i < bag_length; i++) {
            bag[i] = 0; // reset bag
        }
        bag_length = 0;
    }
    roll = check_bag(roll, bag_length, bag);
    bag[bag_length++] = roll;
    switch (roll) {
        case (0): tetromino = tetcreate(TETROMINO_I, '0'); break;
        case (1): tetromino = tetcreate(TETROMINO_J, '1'); break;
        case (2): tetromino = tetcreate(TETROMINO_L, '2'); break;
        case (3): tetromino = tetcreate(TETROMINO_O, '3'); break;
        case (4): tetromino = tetcreate(TETROMINO_S, '4'); break;
        case (5): tetromino = tetcreate(TETROMINO_Z, '5'); break;
        case (6): tetromino = tetcreate(TETROMINO_T, '6'); break;
        default: return NULL;
    }
    return tetromino;
}
