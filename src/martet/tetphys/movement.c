#include "tetphys.h"

void tetaction(char input, struct Tetromino* tetromino){
    switch (input){
        case (UP): tetrotate(tetromino); break;
        case (DOWN): tetfall(tetromino); break;
        case (LEFT):
        case (RIGHT): tetmove(input, tetromino); break;
        default: break;
    }
}

void tetmove(char direction, struct Tetromino* tetromino){
    if (blockmove(direction, &(tetromino->Block1)))