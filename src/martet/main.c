#include <time.h>
#include "../gamefunc/misc/timer.h"
#include "tetbase.h"
#include "tetgfx.h"

const int GAME_SPEED = 800;

int run_martet(SDL_Surface*, SDL_Surface*);

int main(int argc, char** argv){
    int i;
    int j;
    int* score = (int*) malloc(sizeof(int));
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    // Unicode support for hiscore table
    SDL_EnableUNICODE(1);
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return 1;
    }
    SDL_Surface* screen = SDL_SetVideoMode(608, 640, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("martet", "martet");
    SDL_Surface* board = create_surface(320, 640);
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
    bool running = true;
    while (running){
        if (menu_martet(screen, board, menu, score) == KEYEVENT_EXIT)
            break;
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
        manage_hiscores(screen, board, score);
        board_delete();
    }
    menu_destroy(menu);
    SDL_FreeSurface(border);
    SDL_FreeSurface(board);
    free(score);
    SDL_Quit();
    return 0;
}

// run_martet: The game loop. Returns final score.
int run_martet(SDL_Surface* screen, SDL_Surface* board) {
    Tetromino* active_tetromino;
    Tetromino* next_tetromino;
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
    timer_change_alarm_interval(timer, GAME_SPEED);
    timer_start(timer);
    bool running = true;
    while (running){
        int event = process_key_events(active_tetromino, tetaction);
        if (event == KEYEVENT_EXIT)
            exit(0);
        else if (event == KEYEVENT_MENU) {
            if (ingame_menu_martet(screen, board, ingame_menu) == 1)
                running = false;
        }
        else if (event == KEYEVENT_PAUSE)
            pause_martet(screen, board);
        if (timer_update(timer)){
            // check if tetromino dropped to board with tetfall.
            if ( active_tetromino->color == TETROMINO_DELETE )
                ;
            else if ( tetmove('d', active_tetromino) == 0 ) { // if collision
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
            // speed changes every 10 points
            timer_change_alarm_interval(timer, GAME_SPEED / (score/10+1) );
        }
        clear_surface(board, NULL);
        draw_board(board);
        draw_tetromino(board, active_tetromino);
        draw_ghost_tetromino(board, active_tetromino);
        draw_surface(0, 0, board, screen, NULL);
        SDL_Flip(screen);
    }
    menu_destroy(ingame_menu);
    return score;
}

