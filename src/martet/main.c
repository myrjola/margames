
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
    SDL_Surface* boardsurf  = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    screen    = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);
    boardsurf = SDL_SetVideoMode(480, 640, 32, SDL_SWSURFACE);
    board_create();
    active_tetromino = tetcreate(TETROMINO_S);
    int score   = 0;
    int running = 1;
    while (running){
        if (process_key_events(active_tetromino, tetaction)) // if 1 player tries to quit
            running = 0;
        clear_board(boardsurf);
        draw_tetromino(boardsurf, active_tetromino);
        draw_board(boardsurf);
        draw_surface(0, 0, boardsurf, screen);
        SDL_Flip(screen);
        score += check_rows();
        // tetaction('d', active_tetromino);
        // SDL_Delay(1000);
    }
    return 0;
}
