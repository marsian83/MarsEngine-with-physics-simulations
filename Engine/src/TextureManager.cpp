#include "TextureManager.hpp"

SDL_Texture *TextureManager::loadTexture(const char *filename)
{
    SDL_Surface *tmpSurf = IMG_Load(filename);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Engine::renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);
    return tex;
}

void TextureManager::draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Engine::renderer, tex, &src, &dst, NULL, NULL, flip);
}