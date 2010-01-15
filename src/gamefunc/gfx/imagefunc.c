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

void clear_surface(SDL_Surface* surface, SDL_Rect* cliprect){
    SDL_FillRect(surface, cliprect, SDL_MapRGB(surface->format, 0, 0, 0));
    return;
}

int draw_text(int x, int y, SDL_Surface* screen, const char* text)
{
    TTF_Font *font;
    font = TTF_OpenFontIndex("data/Tuffy.ttf", 18, 0);
    if(!font) {
        printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Color color = {255,255,255};
    SDL_Surface *text_surface;
    text_surface = TTF_RenderText_Solid(font, text, color);
    if (text_surface)
        draw_surface(x, y, text_surface, screen, NULL);
    else
        return 0;
    return 1;
}
