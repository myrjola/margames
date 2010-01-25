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

SDL_Surface* draw_text_helper(int x, int y, SDL_Surface* surf, void* text,
                              Uint8 r, Uint8 b, Uint8 g, bool unicode) {
    if (!font) {
        font = TTF_OpenFont("../data/Tuffy.ttf", 18);
        if (!font) {
            // handle error
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }
    }
    SDL_Color color = {r, b, g};
    SDL_Surface* text_surface;
    if (unicode) {
        text_surface = TTF_RenderUNICODE_Solid(font, (Uint16*) text, color);
    }
    else {
        text_surface = TTF_RenderText_Solid(font, (char*) text, color);
    }
    if (surf == NULL) {
        return text_surface;
    }
    draw_surface(x, y, text_surface, surf, NULL);
    SDL_FreeSurface(text_surface);
    return NULL;
}

SDL_Surface* draw_text(int x, int y, SDL_Surface* surf, char* text,
                       Uint8 r, Uint8 b, Uint8 g) {
    return draw_text_helper(x, y, surf, text, r, b, g, false);
}

SDL_Surface* draw_text_unicode(int x, int y, SDL_Surface* surf, Uint16* text,
                               Uint8 r, Uint8 b, Uint8 g) {
    return draw_text_helper(x, y, surf, text, r, b, g, true);
}

SDL_Surface* draw_text_multiline_helper(int x, int y, SDL_Surface* surf,
                                        void* text, Uint8 r, Uint8 b, Uint8 g,
                                        bool unicode) {
    int line_y = 0;
    // count linebreaks
    int i = 0;
    int line_count = 1;
    if (unicode) {
        while (((Uint16*) text)[i++] & 0x0000ffff) { // While not NULL
            if (((Uint16*) text)[i] == (Uint16) 0xfeff0013 ) {
                line_count++;
            }
        }
    }
    else {
        while (((char*) text)[i++]) {
            if (((char*) text)[i] == '\n' ) {
                line_count++;
            }
        }
    }
    int w = 300;
    int h = line_count*25;
    SDL_Surface* text_surface = create_surface(w, h);
    i = 0;
    if (unicode) {
        while(((Uint16*) text)[i] & 0x0000ffff) { // While not NULL
            draw_text_helper(x, line_y, text_surface, text + i, r, b, g, false);
            line_y += 25;
            if (--line_count) { // If there's lines left jump to next line
                while (((Uint16*) text)[i++] != (Uint16) 0xfeff0013)
                    ;
            }
        }
    } 
    else {
        while(((char*) text)[i]) {
            draw_text_helper(x, line_y, text_surface, text + i, r, b, g, false);
            line_y += 25;
            if (--line_count) { // If there's lines left jump to next line
                while (((char*) text)[i++] != '\n')
                    ;
            }
        }
    }
    if (surf == NULL) {
        return text_surface;
    }
    draw_surface(x, y, text_surface, surf, NULL);
    SDL_FreeSurface(text_surface);
    return NULL;
}

SDL_Surface* draw_text_multiline(int x, int y, SDL_Surface* surf,
                                 char* text, Uint8 r, Uint8 b, Uint8 g) {
    return draw_text_multiline_helper(x, y, surf, (void*) text, r, b, g, false);
}

SDL_Surface* draw_text_multiline_unicode(int x, int y, SDL_Surface* surf,
                                         Uint16* text,
                                         Uint8 r, Uint8 b, Uint8 g) {
    return draw_text_multiline_helper(x, y, surf, (void*) text, r, b, g, true);
}
