#import "tetromino.h"

// tetcreate: creates a tetromino and passes the pointer to it
struct* tetcreate(const int coordinates[4][2]){
    // allocate memory for tetromino
    struct* tetromino;
    tetromino = (struct Tetromino*) malloc(sizeof(struct Tetromino));
    // create the tetromino
    tetromino->Block1.x = coordinates[0][0];
    tetromino->Block2.x = coordinates[0][1];
    tetromino->Block3.x = coordinates[0][2];
    tetromino->Block4.x = coordinates[0][3];
    tetromino->Block1.y = coordinates[1][0];
    tetromino->Block2.y = coordinates[1][1];
    tetromino->Block3.y = coordinates[1][2];
    tetromino->Block4.y = coordinates[1][3];
    // init direction
    tetromino->direction = 0;
}

// tetrotate: rotates the tetromino 90 degrees clockwise
void tetrotate(struct Tetromino* tetromino){
    // get rotation angle and change direction
    double angle = rotationangle(tetromino->direction)
    // Block1 as pivot point
    pointrotate(tetromino->Block2, angle);
    pointrotate(tetromino->Block3, angle);
    pointrotate(tetromino->Block4, angle);
    return;
}


// rotationangle: changes Tetromino.direction and
//                returns the angle in radians
double rotationangle(int* direction){
    (*direction)++;
    if (direction == 4)
        *direction = 0;
    return (*direction * 3.14 / 2);
}

// pointrotate: rotates point in 90 degrees clockwise
//              relative to origo. Used for tetromino
//              blocks.
void pointrotate(struct Block* block, double angle){
    // cast the coordinates to doubles
    // needed by the math functions
    double x = (double) block->x;
    double y = (double) block->y;
    // distance to origo
    double distance = sqrt((x*x + y*y));
    // rotation using trigonometry
    x = distance * cos(angle);
    y = distance * sin(angle);
    // casting the doubles back to int,
    // automatic approximation should occur
    block->x = (int) x;
    block->y = (int) y;
}
