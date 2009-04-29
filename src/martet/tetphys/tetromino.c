#include "tetromino.h"

const int TETROMINO_I[4][2] = {{0, 0},
                               {0, -1},
                               {0, 1},
                               {0, 2}};

const int TETROMINO_J[4][2] = {{0, 0},
                               {-1, 0},
                               {0, -1},
                               {0, -2}};

const int TETROMINO_L[4][2] = {{0, 0},
                               {0, -1},
                               {0, -2},
                               {1, 0}};

const int TETROMINO_O[4][2] = {{0, 0},
                               {1, 1},
                               {1, 0},
                               {0, 1}};

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

// Colors of the blocks used by the block writing function
enum colors {RED = 0, GREEN, BLUE, YELLOW, CYAN,
             ORANGE, MAGENTA, BROWN, GREY, OLIVE};

// tetcreate: creates a tetromino and passes the pointer to it
struct Tetromino* tetcreate(const int coordinates[4][2]){
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

    // set the position up and to the middle on the board
    tetromino->position[0] = 5; // width of board = 10
    tetromino->position[1] = 2; // 0 is up 20 is down
    // lazy as I am just choosing random color, looks as pretty anyways.
    // in int to char conversion you must add '0' to get the right ASCII code
    tetromino->color = (char) ((rand() % 10) + '0');
    return tetromino;
}

// tetrotate: rotates the tetromino 90 degrees clockwise
void tetrotate(struct Tetromino* tetromino){
    // Block1 allways as pivot point
    pointrotate(&(tetromino->Block2));
    pointrotate(&(tetromino->Block3));
    pointrotate(&(tetromino->Block4));
    return;
}

// pointrotate: rotates point in 90 degrees clockwise
//              relative to origo. Used for tetromino
//              blocks.
void pointrotate(struct Block* block){
    // cast the coordinates to doubles
    // needed by the math functions
    double x = (double) block->x;
    double y = (double) block->y;
    // distance to origo
    double distance = sqrt((x*x + y*y));
    // calculate the initial direction in radians
    double angle;
    if (x != 0){
        angle = acos(x / distance);
        // angle range 0 , 180 if y not checked
        if (y < 0)
            angle = -angle;
    }
    else
        angle = asin(y / distance);

    angle += 1.57;

    // rotation using trigonometry
    x = distance * cos(angle);
    y = distance * sin(angle);
    // approximate the doubles to integers
    block->x = (int) (x >= 0) ? (x + 0.5) : (x - 0.5);
    block->y = (int) (y >= 0) ? (y + 0.5) : (y - 0.5);
    return;
}
