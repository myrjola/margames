
#include <time.h>
#include "tetphys/tetromino.h"
#include "tetphys/tetphys.h"
#include "tetgfx/tilegfx.h"
#include "tetbase/board.h"
#include "../gamefunc/input/keyeventinput.h"
#include "../gamefunc/gfx/imagefunc.h"
#include "../gamefunc/misc/timer.h"

int runmartet(SDL_Surface*);

int main(int argc, char** argv){
    SDL_Surface* screen     = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    screen = SDL_SetVideoMode(320, 640, 32, SDL_SWSURFACE);
    while (true){
        runmartet(screen);
        board_delete();
        SDL_Surface* game_over_img = load_image("data/gameover.png");
        draw_surface(110, 320, game_over_img, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(5000);
    }
    return 0;
}

int runmartet(SDL_Surface* screen){
    struct Tetromino* active_tetromino;
    srand((unsigned) time(NULL));
    board_create();
    active_tetromino = tetcreaterand();
    int score = 1;
    struct Timer* timer = create_timer();
    timer_change_alarm_interval(timer, 200);
    timer_start(timer);
    int running = 1;
    while (running){
        if (process_key_events(active_tetromino, tetaction)) // if 1 player tries to quit
            running = 0;
        if (timer_update(timer)){
            if ( !tetmove('d', active_tetromino) ){
                drop_tetromino(active_tetromino);
                active_tetromino = tetcreaterand();
                if ( active_tetromino == NULL )
                    break;
                check_rows(&score);
                timer_change_alarm_interval(timer, 200 / score);
            }
        }
        clear_board(screen);
        draw_tetromino(screen, active_tetromino);
        draw_board(screen);
        SDL_Flip(screen);
    }
    
}