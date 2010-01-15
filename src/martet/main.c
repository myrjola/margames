
#include <stdlib.h>
#include <time.h>
#include "tetphys/tetromino.h"
#include "tetphys/tetphys.h"
#include "tetgfx/tilegfx.h"
#include "tetbase/board.h"
#include "../gamefunc/input/keyeventinput.h"
#include "../gamefunc/gfx/imagefunc.h"
#include "../gamefunc/misc/timer.h"
#include "../gamefunc/misc/miscutils.h"

int run_martet(SDL_Surface*, SDL_Surface*);
int update_status_bar(struct Tetromino*, SDL_Surface*, int);

int main(int argc, char** argv){
    SDL_Surface* screen     = NULL;
    SDL_Surface* board     = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return 1;
    }
    screen = SDL_SetVideoMode(608, 640, 32, SDL_SWSURFACE);
    board  = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 640, 32,
                                                  0, 0, 0, 0);
    SDL_Surface* border = load_image("data/tetborder.png");
    draw_surface(321, 0, border, screen, NULL);
    draw_text(400, 32, screen, "Next tetromino:");
    draw_text(330, 200, screen, "Score: ");
    // The game loop begins
    while (true){
        run_martet(screen, board);
        board_delete();
        SDL_Surface* game_over_img = load_image("data/gameover.png");
        draw_surface(110, 320, game_over_img, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(5000);
        exit(0);
    }
    return 0;
}

int run_martet(SDL_Surface* screen, SDL_Surface* board){
    struct Tetromino* active_tetromino;
    struct Tetromino* next_tetromino;
    int score = 1;
    srand((unsigned) time(NULL));
    board_create();
    next_tetromino   = tetcreaterand();
    update_status_bar(next_tetromino, screen, score);
    active_tetromino = tetcreaterand();
    active_tetromino->position[0] = 4;
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
                active_tetromino = next_tetromino;
                next_tetromino   = tetcreaterand();
                if ( next_tetromino == NULL )
                    break;
                check_rows(&score);
                update_status_bar(next_tetromino, screen, score);
                timer_change_alarm_interval(timer, 400 / (score/10+1) );
            }
        }
        clear_surface(board, NULL);
        draw_tetromino(board, active_tetromino);
        draw_board(board);
        draw_surface(0, 0, board, screen, NULL);
        SDL_Flip(screen);
    }
}

int update_status_bar(struct Tetromino* next_tetromino, SDL_Surface* screen, int score){
    // update score
    char scorebuf[65];
    SDL_Rect cliprect;
    cliprect.x = 400;
    cliprect.y = 200;
    cliprect.w = 208;
    cliprect.h = 20;
    itoa(score, scorebuf);
    clear_surface(screen, &cliprect);
    draw_text(400, 200, screen, scorebuf);
    // update next tetromino image
    cliprect.x = 416;
    cliprect.y = 64;
    cliprect.w = 128;
    cliprect.h = 128;
    clear_surface(screen, &cliprect);
    next_tetromino->position[0] = 14;
    next_tetromino->position[1] = 3;
    draw_tetromino(screen, next_tetromino);
    next_tetromino->position[0] = 5;
    next_tetromino->position[1] = 1;
}
