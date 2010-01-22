#include "imagefunc.h"

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

SDL_Surface* draw_text(int x, int y, SDL_Surface* surf, const char* text, Uint8 r, Uint8 b, Uint8 g)
{
    if (!font) {
        font = TTF_OpenFont("../data/Tuffy.ttf", 18);
    }
    if (!font) {
        // handle error
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    SDL_Color color = {r, b, g};
    SDL_Surface *text_surface;
    text_surface = TTF_RenderText_Solid(font, text, color);
    if (surf == NULL)
        return text_surface;
    if (text_surface)
        draw_surface(x, y, text_surface, surf, NULL);
    else
        return NULL;
    SDL_FreeSurface(text_surface);
    return NULL;
}

