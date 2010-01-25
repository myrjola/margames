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
    const Uint16 UNICODE_NULL = (Uint16) 0xfeff0000;
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
        Uint16* name = (Uint16*) calloc(12, sizeof(Uint16));
        name[0] = UNICODE_NULL;
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
            draw_text_unicode(100, 400, screen, name, 255, 255, 255);
            SDL_Flip(screen);
        }
        SDL_FreeSurface(grats_text_surf);
        add_hiscore(hiscores, *score, name);
        free(name);
    }
    save_hiscores(hiscores);
    // Show the high score table
    Uint16* hiscore_table = (Uint16*) calloc(SCORE_TABLE_LENGTH*32, sizeof(char));
    Uint16* p_hiscore_table = hiscore_table;
    Uint16* score_line;
    Uint16* p_score_line;
    for (i = 0; i < SCORE_TABLE_LENGTH; i++) {
//         score_line = get_scoreline(hiscores + i);
//         p_score_line = score_line;
        // Unicode strcat
//         while (*p_score_line != UNICODE_NULL) {
//             *(p_hiscore_table++) = *(p_score_line++);
//         }
        free(score_line);
    }
    SDL_Surface* hiscore_table_surf = draw_text_multiline_unicode(0, 0, NULL,
                                                                  hiscore_table,
                                                                  255, 255, 255);
    clear_surface(board, NULL);
    draw_surface_centered(hiscore_table_surf, board);
    SDL_FreeSurface(hiscore_table_surf);
    draw_surface(0, 0, board, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(2000);
    return running;
}



