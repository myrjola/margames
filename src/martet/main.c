#include "tetphys/tetromino.h"
#include "tetgfx/asciigfx.h"
#include "tetgfx/tilegfx.h"
#include "tetbase/board.h"

int main(int argc, char** argv){
    struct Tetromino* active_tetromino;
    SDL_Surface* screen     = NULL;
    SDL_Surface* boardsurf  = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    screen    = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    board_create();
    boardsurf = 
    
    return 0;
}
