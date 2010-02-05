#include "imagefunc.h"

SDL_Surface* create_surface(int w, int h){
    SDL_Surface* surface_unoptimized = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h,
                                                            32, 0, 0, 0, 0);
    SDL_Surface* surface = SDL_DisplayFormat(surface_unoptimized);
    SDL_FreeSurface(surface_unoptimized);
    return surface;
}

SDL_Surface* load_image(const char* filename){
    SDL_Surface* loadedImage    = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(filename);
    if (loadedImage != NULL){
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        return optimizedImage;
    }
    return NULL;
}

void draw_surface(int x, int y, SDL_Surface* source, SDL_Surface* target, SDL_Rect* clip){
    /* Temporary rect for offset */
    SDL_Rect temprect;
    temprect.x = x;
    temprect.y = y;
    /* Blitting time */
    SDL_BlitSurface(source, clip, target, &temprect);
}

void draw_surface_centered(SDL_Surface* source, SDL_Surface* target) {
    /* Temporary rect for offset */
    SDL_Rect temprect;
    temprect.x = (target->w / 2) - (source->w / 2);
    temprect.y = (target->h / 2) - (source->h / 2);
    /* Blitting time */
    SDL_BlitSurface(source, NULL, target, &temprect);
}

void clear_surface(SDL_Surface* surface, SDL_Rect* cliprect){
    SDL_FillRect(surface, cliprect, SDL_MapRGB(surface->format, 0, 0, 0));
    return;
}


TTF_Font* font = NULL;

SDL_Surface* draw_text(int x, int y, SDL_Surface* surf, char* text,
                              Uint8 r, Uint8 b, Uint8 g) {
    if (!font) {
        font = TTF_OpenFont("../data/retro.ttf", 11);
        if (!font) {
            // handle error
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }
    }
    SDL_Color color = {r, b, g};
    SDL_Surface* text_surface;
    text_surface = TTF_RenderUTF8_Solid(font, text, color);
    if (surf == NULL) {
        return text_surface;
    }
    draw_surface(x, y, text_surface, surf, NULL);
    SDL_FreeSurface(text_surface);
    return NULL;
}

SDL_Surface* draw_text_multiline(int x, int y, SDL_Surface* surf,
                                 char* text, Uint8 r, Uint8 b, Uint8 g) {
    char text_to_draw[40];
    int start_pos;
    int end_pos;
    int line_y = 0;
    // count linebreaks
    int i = 0;
    int line_count = 1;
    while (((char*) text)[i++]) {
        if (((char*) text)[i] == '\n' ) {
            line_count++;
        }
    }
    int w = 300;
    int h = line_count*25;
    SDL_Surface* text_surface = create_surface(w, h);
    i = 0;
    while(text[i]) {
        start_pos = i;
        end_pos = 0;
        if (--line_count) { // Find next linebreak.
            while (text[i++] != '\n' && text[i])
                end_pos++;
        }
        text_to_draw[0] = '\0';
        strncat(text_to_draw, text + start_pos, end_pos);
        draw_text(x, line_y, text_surface, text_to_draw, r, b, g);
        line_y += 25;
    }
    if (surf == NULL) {
        return text_surface;
    }
    draw_surface(x, y, text_surface, surf, NULL);
    SDL_FreeSurface(text_surface);
    return NULL;
}