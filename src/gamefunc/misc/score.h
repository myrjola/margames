// A simple hiscore system.
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL/SDL.h>

#ifndef SCORE_H_
#define SCORE_H_

enum {SCORE_TABLE_LENGTH = 10};

struct Score{
    Uint16 name[32];
    int points;
};

// get_hiscores: Returns the high score list as a malloc'd string.
struct Score* get_hiscores();

// add_hiscore: Adds a high score to the list. Returns position or -1 if it
// didn't get to the list.
int add_hiscore(struct Score* hiscores, int score, Uint16* name);

// save_hiscores: Saves high scores to a file. Returns true succesful and false
// on error
bool save_hiscores(struct Score* hiscores);

#endif