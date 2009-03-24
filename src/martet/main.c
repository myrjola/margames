#include "tetphys/tetromino.h"
#include "tetphys/tetphys.h"
#include "tetgfx/asciigfx.h"
#include "tetgfx/fillrectgfx.h"
#include "tetbase/board.h"
#include "../gamefunc/input/keyeventinput.h"

int main(int argc, char** argv){
    struct Tetromino* active_tetromino;
    SDL_Surface* screen     = NULL;
    SDL_Surface* boardsurf  = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    screen    = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    boardsurf = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    board_create();
    int score   = 0;
    int running = 1;
    while (running){
        process_key_events(active_tetromino, tetaction);
        clear_board(boardsurf);
        draw_board(boardsurf);
        score += check_rows();
    }
    return 0;
}
