#import <stdlib.h>
#import <math.h>

// Tetrominoes as coordinates
const int TETROMINO_I[4][2] = {{0, 0},
                               {0, -1},
                               {0, 1},
                               {0, 2}};

const int TETROMINO_J[4][2] = {{0, 0},
                               {-1, 0},
                               {0, -1},
                               {0, -2};

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


struct Block{
    int x;
    int y;
};

struct Tetromino{
    Block Block1;
    Block Block2;
    Block Block3;
    Block Block4;
    // direction 0 to 3 used for the 
    // rotation algorithm
    int direction;
};

// tetcreate: creates a tetromino and passes the pointer to it
struct* tetcreate(const int);

// tetrotate: rotates the tetromino 90 degrees clockwise
void tetrotate(struct Tetromino*);

// rotationangle: changes Tetromino.direction and
//                returns the angle in radians
double rotationangle(int*);

// pointrotate: rotates point in 90 degrees clockwise
//              relative to origo. Used for tetromino
//              blocks.
void pointrotate(struct Block*, double);

