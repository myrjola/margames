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
}