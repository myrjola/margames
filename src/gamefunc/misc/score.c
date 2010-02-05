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

int add_hiscore(struct Score* hiscores, int points, char* name) {
    int i;
    struct Score newscore;
    newscore.points = points;
    strcpy(newscore.name, name);
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
    if( fclose(fp) ) {
        printf("Cannot close scores.dat.\n");
        return false;
    }
    return true;
}

char* get_scoreline(struct Score* score, int placement) {
    char* score_string = (char*) calloc(40, sizeof(char));
    itos(placement, score_string);
    strcat(score_string, ". ");
    strcat(score_string, score->name);
    char points[10];
    itos(score->points, points);
    strcat(score_string, " ");
    strcat(score_string, points);
    strcat(score_string, " points.\n\n");
    return score_string;
}
