#include <string.h>
#include "simplemenu.h"

struct Menu* menu_create() {
    struct Menu* menu = (struct Menu*) malloc(sizeof(struct Menu));
    menu->elements = (struct MenuElement*) calloc(20, sizeof(struct MenuElement));
    menu->active_element = NULL;
    menu->length = 0;
    return menu;
}

void menu_destroy(struct Menu* menu) {
    int i;
    for (i = 0; i < menu->length; i++) {
        free(menu->elements[i].text);
    }
    free(menu->elements);
    free(menu);
}

void menu_addelement(struct Menu* menu, char* text) {
    struct MenuElement* element = &menu->elements[menu->length]; // next free element
    element->text = (char*) calloc(32, sizeof(char));
    strcpy(element->text, text);
    element->active = 0;
    element->next = &menu->elements[0]; // wraps around to first element
    element->previous = &menu->elements[menu->length - 1];
    menu->elements[menu->length - 1].next = element; // change the former last element's next
    menu->elements[0].previous = element;
    element->index = ++menu->length + 1; // 0 and 1 reserved for KEYEVENT_NOTHING and KEYEVENT_EXIT
}

// menu_action - function to be passed to process_key_events
int menu_action(char input, void* voidmenu){
    struct Menu* menu = voidmenu;
    struct MenuElement* element;
    switch (input){
        case ('u') :element = menu->active_element;
                    element->active = 0;
                    menu->active_element = element->previous;
                    menu->active_element->active = 1;
                    break;
        case ('d') :element = menu->active_element;
                    element->active = 0;
                    menu->active_element = element->next;
                    menu->active_element->active = 1;
                    break;
        case ('\n'): return menu->active_element->index; break;
        default: break;
    }
    return 0;
}

// draw_menu - draws menu centered on surface
void draw_menu(struct Menu* menu, SDL_Surface* destination, int oldx, int oldy) {
    struct MenuElement* element;
    int i;
    int x = 0;
    int y = 0;
    int w = 200;
    int h = menu->length*25;
    SDL_Surface* menusurf = create_surface(w, h);
    SDL_Surface* menutextsurf;
    for (i = 0; i < menu->length; i++) {
        element = &menu->elements[i];
        if (element->active) { // draw active element red
            menutextsurf = draw_text(0, 0, NULL, element->text, 255, 0, 0);
            draw_surface(x, y,
                         menutextsurf,
                         menusurf, NULL);
            SDL_FreeSurface(menutextsurf);
        }
        else {
            menutextsurf = draw_text(0, 0, NULL, element->text, 255, 255, 255);
            draw_surface(x, y, //draw inactive element white
                         menutextsurf,
                         menusurf, NULL);
            SDL_FreeSurface(menutextsurf);
        }
        y += 25;
    }
    draw_surface_centered(menusurf, destination);
    SDL_FreeSurface(menusurf);
}