
#include "tetphys/tetromino.h"
#include "tetphys/tetphys.h"
#include "tetgfx/asciigfx.h"
#include "tetgfx/fillrectgfx.h"
#include "tetbase/board.h"
#include "../gamefunc/input/keyeventinput.h"
#include "../gamefunc/gfx/imagefunc.h"

int main(int argc, char** argv){
    struct Tetromino* active_tetromino;
    SDL_Surface* screen     = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    screen = SDL_SetVideoMode(320, 640, 32, SDL_SWSURFACE);
    board_create();
    active_tetromino = tetcreate(TETROMINO_O);
    int score   = 0;
    int running = 1;
    while (running){
        if (process_key_events(active_tetromino, tetaction)) // if 1 player tries to quit
            running = 0;
        SDL_Delay(250);
        if ( !(tetmove('d', active_tetromino)) ){
            drop_tetromino(active_tetromino);
            active_tetromino = tetcreate(TETROMINO_O);
        }
        clear_board(screen);
        draw_tetromino(screen, active_tetromino);
        draw_board(screen);
        SDL_Flip(screen);
        score += check_rows();
    }
    return 0;
}
