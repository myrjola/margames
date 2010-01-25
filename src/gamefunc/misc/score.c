#include "score.h"

struct Score* get_hiscores() {
    FILE* fp;
    struct Score* hiscores = (struct Score*) calloc(SCORE_TABLE_LENGTH,
                                                    sizeof(struct Score));
    int i;
    if((fp = fopen("scores.dat", "rb")) == NULL) {
        printf("Scores.dat doesn't exist. Creating new one\n");
        for (i = 0; i < SCORE_TABLE_LENGTH; i++) {
            hiscores[i].points = -1; // Unitialized scores have -1 points
        }
        save_hiscores(hiscores);
        return get_hiscores();
    }
    fread(hiscores, sizeof(struct Score), SCORE_TABLE_LENGTH, fp);
    if( fclose(fp) ) {
        printf("Cannot close scores.dat\n");
    }
    return hiscores;
}

int add_hiscore(struct Score* hiscores, int points, Uint16* name) {
    int i;
    struct Score newscore;
    newscore.points = points;
    for (i = 0; i < 32; i++) {
        newscore.name[i] = name[i];
    }
    for (i = 0; i < SCORE_TABLE_LENGTH; i++) {
        if (hiscores[i].points == -1 ) { // not initialized
            memcpy(hiscores + i, &newscore, sizeof(struct Score));
            return i;
        }
        if (points > hiscores[i].points) {
            int position = i;
            struct Score temp;
            memcpy(&temp, hiscores + i, sizeof(struct Score));
            memcpy(hiscores + i, &newscore, sizeof(struct Score));
            while (++i < SCORE_TABLE_LENGTH) {
                struct Score temp2;
                memcpy(&temp2, hiscores + i, sizeof(struct Score));
                memcpy(hiscores + i, &temp, sizeof(struct Score));
                memcpy(&temp, &temp2, sizeof(struct Score));
            }
            return position;
        }
    }
    return -1;
}

bool save_hiscores(struct Score* hiscores) {
    FILE* fp;
    if((fp = fopen("scores.dat", "wb")) == NULL) {
        printf("Cannot open scores.dat.\n");
        return false;
    }
    fwrite(hiscores, sizeof(struct Score), SCORE_TABLE_LENGTH, fp);
    free(hiscores);
    if( fclose(fp) ) {
        printf("Cannot close scores.dat.\n");
        return false;
    }
    return true;
}

Uint16* get_scoreline(struct Score* score) {
    Uint16* score_string_u = (Uint16*) calloc(30, sizeof(Uint16));
    char* points_string = (char*) calloc(10, sizeof(char));
    Uint16 points_string_u[10];
    itos(score->points, points_string);
    int i = 0;
    // utf-16 begins with 0xfeff
    Uint16 magic_number = (Uint16) 0xfeff0000;
    // convert points to unicode
    while (points_string[i++]){
        points_string_u[i] = ((Uint16) points_string[i]) | magic_number;
    }
    int j = 0;
    // insert name
    while (score->name[j++]) {
        score_string_u[j] = score->name[j];
    }
    //fill with '*'
    char star = '*';
    Uint16 unistar = (Uint16) star | magic_number;
    while (i + j++ <=27) {
        score_string_u[j] = unistar;
    }
    // insert points
    while (i--) {
        score_string_u[j++] = (*points_string_u)++;
    }
    free(points_string);
    score_string_u[j] = magic_number; // unicode null
    return score_string_u;
}
