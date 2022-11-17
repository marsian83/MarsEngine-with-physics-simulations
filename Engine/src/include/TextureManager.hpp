#pragma once

#include "Engine.hpp"

class TextureManager
{
private:
public:
    static SDL_Texture *loadTexture(const char *filename);
    static void draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip);
};