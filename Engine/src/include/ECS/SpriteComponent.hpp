#pragma once

#include "Components.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include <map>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect src, dst;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    SpriteComponent(const char *path)
    {
        setSprite(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setSprite(const char *path)
    {
        texture = TextureManager::loadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        src.x = src.y = 0;
        src.w = transform->width;
        src.h = transform->height;
    }

    void update() override
    {
        dst.w = transform->width * transform->scale;
        dst.h = transform->height * transform->scale;
        dst.x = static_cast<int>(transform->position.x);
        dst.y = static_cast<int>(transform->position.y);
    }

    void draw() override
    {
        TextureManager::draw(texture, src, dst, spriteFlip);
    }
};