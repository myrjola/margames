#include "tetgfx.h"

void pause_martet(SDL_Surface* screen, SDL_Surface* board) {
    clear_surface(board, NULL);
    draw_surface(0, 0, board, screen, NULL);
    draw_text(74, 315, screen, "PAUSED, 'p' to continue", 255, 255, 255);
    SDL_Flip(screen);
    int pause_action(char c, void* whatever) {
        return KEYEVENT_NOTHING;
    }
    while (true) {
        int event = process_key_events(NULL, pause_action);
        if (event == KEYEVENT_PAUSE)
            return;
        else if (event == KEYEVENT_EXIT)
            exit(0);
    }
}

int menu_martet(SDL_Surface* screen, SDL_Surface* board,
                struct Menu* menu, int* score) {
    int index; // ...of menu item pressed 0 if none
    clear_surface(board, NULL);
    draw_surface(0, 0, board, screen, NULL);
    bool running = true;
    while (running) {
        switch(process_key_events(menu, menu_action)) {
            case (KEYEVENT_EXIT): running = false; break;
            case (2): *score = run_martet(screen, board);
                      return 0; break;
            case (3): running = false; break;
        }
        draw_menu(menu, board, 120, 300);
        draw_surface(0, 0, board, screen, NULL);
        SDL_Flip(screen);
    }
    return KEYEVENT_EXIT;
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

int update_status_bar(Tetromino* next_tetromino, SDL_Surface* screen,
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


