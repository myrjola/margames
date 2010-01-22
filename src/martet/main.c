
#include <stdlib.h>
#include <time.h>
#include "tetbase.h"
#include "tilegfx.h"
#include "../gamefunc/input/keyeventinput.h"
#include "../gamefunc/gfx/imagefunc.h"
#include "../gamefunc/misc/timer.h"
#include "../gamefunc/misc/miscutils.h"
#include "../gamefunc/misc/simplemenu.h"

int run_martet(SDL_Surface*, SDL_Surface*);
void pause_martet(SDL_Surface*, SDL_Surface*);
int menu_martet(SDL_Surface*, SDL_Surface*, struct Menu*);
int ingame_menu_martet(SDL_Surface*, SDL_Surface*, struct Menu*);
int update_status_bar(struct Tetromino*, SDL_Surface*, int);

int main(int argc, char** argv){
    SDL_Surface* screen     = NULL;
    SDL_Surface* board     = NULL;
    int i;
    int j;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error: SDL didn't initialize\n");
        return 1;
    }
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return 1;
    }
    screen = SDL_SetVideoMode(608, 640, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("martet", "martet");
    board  = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 640, 32,
                                                  0, 0, 0, 0);
    SDL_Surface* border = load_image("../data/tetborder.png");
    draw_surface(321, 0, border, screen, NULL);
    draw_text(410, 35, screen, "Next tetromino:", 255, 255, 255),
    draw_text(330, 200, screen, "Score: ", 255, 255, 255);
    // create menu
    struct Menu* menu = menu_create();
    menu_addelement(menu, "Start Game");
    menu_addelement(menu, "Quit");
    menu->active_element = &menu->elements[0];
    menu->active_element->active = 1;
    // The game loop begins
    while (true){
        menu_martet(screen, board, menu);
        // fill the board with blocks on game over
        for (i = 0; i < BOARD_HEIGHT; i++) {
            char* line = get_board_line(i);
            for (j = 0; j < BOARD_WIDTH; j++) {
                line[j] = rand() % 7 + '0';
            }
            draw_board(board);
            draw_surface(0, 0, board, screen, NULL);
            SDL_Flip(screen);
            SDL_Delay(50);
        }
        board_delete();
    }
    return 0;
}

int run_martet(SDL_Surface* screen, SDL_Surface* board){
    struct Tetromino* active_tetromino;
    struct Tetromino* next_tetromino;
    // create menu
    struct Menu* ingame_menu = menu_create();
    menu_addelement(ingame_menu, "Continue");
    menu_addelement(ingame_menu, "Quit Current Game");
    ingame_menu->active_element = &ingame_menu->elements[0];
    ingame_menu->active_element->active = 1;
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
        int event = process_key_events(active_tetromino, tetaction);
        if (event == KEYEVENT_EXIT)
            exit(0);
        else if (event == KEYEVENT_MENU) {
            if (ingame_menu_martet(screen, board, ingame_menu) == 1)
                running = 0;
        }
        else if (event == KEYEVENT_PAUSE)
            pause_martet(screen, board);
        if (timer_update(timer)){
            // check if tetromino dropped to board with tetfall.
            if ( active_tetromino->color == TETROMINO_DELETE )
                ;
            else if ( !tetmove('d', active_tetromino) ) { // if collision
                place_tetromino(active_tetromino);
                active_tetromino->color = TETROMINO_DELETE;
            }
            if ( active_tetromino->color == TETROMINO_DELETE ) {
                active_tetromino = next_tetromino;
                next_tetromino   = tetcreaterand();
            }
            if ( next_tetromino == NULL )
                break;
            check_rows(&score);
            update_status_bar(next_tetromino, screen, score);
            timer_change_alarm_interval(timer, 400 / (score/10+1) );
        }
        clear_surface(board, NULL);
        draw_board(board);
        draw_tetromino(board, active_tetromino);
        draw_ghost_tetromino(board, active_tetromino);
        draw_surface(0, 0, board, screen, NULL);
        SDL_Flip(screen);
    }
    menu_destroy(ingame_menu);
}

int pause_action(char c, void* whatever) {
    return KEYEVENT_NOTHING;
}

void pause_martet(SDL_Surface* screen, SDL_Surface* board) {
    clear_surface(board, NULL);
    draw_surface(0, 0, board, screen, NULL);
    draw_text(74, 315, screen, "PAUSED, 'p' to continue", 255, 255, 255);
    SDL_Flip(screen);
    while (true) {
        int event = process_key_events(NULL, pause_action);
        if (event == KEYEVENT_PAUSE)
            return;
        else if (event == KEYEVENT_EXIT)
            exit(0);
    }
}

int menu_martet(SDL_Surface* screen, SDL_Surface* board, struct Menu* menu) {
    int index; // ...of menu item pressed 0 if none
    clear_surface(board, NULL);
    draw_surface(0, 0, board, screen, NULL);
    while (true) {
        switch(process_key_events(menu, menu_action)) {
            case (KEYEVENT_EXIT): exit(2);break;
            case (2): run_martet(screen, board);
                      return 0; break;
            case (3): exit(2); break;
        }
        draw_menu(menu, board, 120, 300);
        draw_surface(0, 0, board, screen, NULL);
        SDL_Flip(screen);
    }
    return 1;
}

int ingame_menu_martet(SDL_Surface* screen, SDL_Surface* board,
                       struct Menu* menu) {
    int index; // ...of menu item pressed 0 if none
    clear_surface(board, NULL);
    draw_surface(0, 0, board, screen, NULL);
    while (true) {
        switch(process_key_events(menu, menu_action)) {
            case (1): exit(0);break;
            case (2): return 0; break;
            case (3): return 1; break;
        }
        draw_menu(menu, board, 120, 300);
        draw_surface(0, 0, board, screen, NULL);
        SDL_Flip(screen);
    }
    return 1;
}

int update_status_bar(struct Tetromino* next_tetromino, SDL_Surface* screen,
                      int score){
    // update score
    char scorebuf[65];
    SDL_Rect cliprect;
    cliprect.x = 400;
    cliprect.y = 200;
    cliprect.w = 208;
    cliprect.h = 20;
    itos(score, scorebuf);
    clear_surface(screen, &cliprect);
    draw_text(400, 200, screen, scorebuf, 255, 255, 255);
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
