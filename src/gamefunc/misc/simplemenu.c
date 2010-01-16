#include <string.h>
#include "simplemenu.h"

struct Menu* menu_create() {
    struct Menu* menu = (struct Menu*) malloc(sizeof(struct Menu));
    menu->active_element = NULL;
    menu->length = 0;
    return menu;
}

void menu_destroy(struct Menu* menu) {
    int i;
    for (i = 0; i < menu->length; i++) {
        free(&menu->elements[i].text);
        free(&menu->elements[i]);
    }
    free(menu);
}

void menu_addelement(struct Menu* menu, char* text) {
    struct MenuElement* element = (struct MenuElement*) malloc(sizeof(struct MenuElement));
    element->text = (char*) malloc(sizeof(char) * 32); 
    strcpy(element->text, text);
    element->active = 0;
    menu->elements[menu->length] = *element; // insert element to menu
    element = &menu->elements[menu->length]; // for some reason the address doesn't stay the same
    element->next = &menu->elements[0]; // wraps around to first element
    element->previous = &menu->elements[menu->length - 1];
    menu->elements[menu->length - 1].next = element; // change the former last element's next
    menu->elements[0].previous = element;
    element->index = ++menu->length; 
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

// draw_menu - draws menu on surface, remember to blit to screen and flip
void draw_menu(struct Menu* menu, SDL_Surface* destination, int oldx, int oldy) {
    struct MenuElement* element;
    int i;
    int x = oldx;
    int y = oldy;
    SDL_Rect cliprect;
    cliprect.x = x;
    cliprect.y = y;
    cliprect.w = 65;
    cliprect.h = menu->length*25;
    //clear_surface(destination, &cliprect);
    for (i = 0; i < menu->length; i++) {
        element = &menu->elements[i];
        if (element->active)
            draw_text(x, y, destination, element->text, 255, 0, 0);
        else
            draw_text(x, y, destination, element->text, 255, 255, 255);
        y += 25;
    }
}