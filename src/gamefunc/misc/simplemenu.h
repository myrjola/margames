// simple menu system
#include <stdlib.h>
#include "SDL/SDL.h"
#include "../gfx/imagefunc.h"

#ifndef SIMPLEMENU_H_
#define SIMPLEMENU_H_

struct MenuElement {
    char* text;
    int index;
    struct MenuElement* previous;
    struct MenuElement* next;
    int active;
};

struct Menu {
    struct MenuElement elements[20]; // maximum of 20 elements
    struct MenuElement* active_element;
    int length;
};

struct Menu* menu_create();

void menu_destroy(struct Menu*);

void menu_addelement(struct Menu*, char*);

int menu_action(char c, void*);

void draw_menu(struct Menu*, SDL_Surface*, int, int);

#endif