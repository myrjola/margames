#include "tetgfx.h"

void pause_martet(SDL_Surface* screen, SDL_Surface* board) {
    clear_surface(board, NULL);
    draw_surface(0, 0, board, screen, NULL);
    draw_text(74, 315, screen, "PAUSED, 'p' to continue", 255, 255, 255);
    SDL_Flip(screen);
    // Stub method for process_key_events.
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

bool manage_hiscores(SDL_Surface* screen, SDL_Surface* board, int* score) {
    struct Score* hiscores = get_hiscores();
    // Check if theres a new high score.
    bool enough_points = false;
    int i;
    for (i = 0; i < SCORE_TABLE_LENGTH; i++) {
        if (hiscores[i].points < *score) {
            enough_points = true;
        }
    }
    bool running = true;
    if (enough_points) {
        char* name = (char*) calloc(12, sizeof(char));
        name[0] = 0;
        char* grats_text = "Congratulations! New High Score!\n"
                            "What's your name?";
        SDL_Surface* grats_text_surf = draw_text_multiline(0, 0, NULL,
                                                           grats_text,
                                                           255, 255, 255);
        // Input of the winners name.
        while (running) {
            int event = input_text(name, 12);
            if (event == KEYEVENT_EXIT) {
                running = false;
            }
            else if (event == KEYEVENT_EOL) {
                break;
            }
            clear_surface(board, NULL);
            draw_surface_centered(grats_text_surf, board);
            draw_surface(0, 0, board, screen, NULL);
            draw_text(100, 400, screen, name, 255, 255, 255);
            SDL_Flip(screen);
        }
        SDL_FreeSurface(grats_text_surf);
        add_hiscore(hiscores, *score, name);
        free(name);
    }
    save_hiscores(hiscores);
    // Show the high score table
    char* hiscore_table = (char*) calloc(SCORE_TABLE_LENGTH*40, sizeof(char));
    char* score_line;
    for (i = 0; i < SCORE_TABLE_LENGTH; i++) {
        score_line = get_scoreline(hiscores + i, i + 1);
        strcat(hiscore_table, score_line);
        free(score_line);
    }
    SDL_Surface* hiscore_table_surf = draw_text_multiline(0, 0, NULL,
                                                          hiscore_table,
                                                          255, 255, 255);
    clear_surface(board, NULL);
    draw_surface_centered(hiscore_table_surf, board);
    SDL_FreeSurface(hiscore_table_surf);
    draw_text(10, 600, board, "Press any key to continue", 255, 255, 255);
    draw_surface(0, 0, board, screen, NULL);
    SDL_Flip(screen);
    // Stub method for process_key_events.
    int hiscore_action(char c, void* whatever) {
        return KEYEVENT_ANY_OTHER_KEY;
    }
    while (true) {
        int event = process_key_events(NULL, hiscore_action);
        if (event == KEYEVENT_EXIT) {
            running = false;
            break;
        }
        else if (event != KEYEVENT_NOTHING) {
            break;
        }
    }
    free(hiscore_table);
    return running;
}



