#pragma once

#include "Components.hpp"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <SDL2/SDL.h>
#include <map>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect src, dst;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:
    int animIndex = 0;

    std::map<const char *, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    SpriteComponent(const char *path)
    {
        setSprite(path);
    }

    SpriteComponent(const char *path, bool isAnimated) : animated(isAnimated)
    {
        // Animation idle = Animation(0, 3, 100);
        // Animation walk = Animation(1, 8, 100);

        // animations.emplace("Idle", idle);
        // animations.emplace("Walk", walk);
        // play("Walk");
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

        if (animated)
        {
            src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        src.y = animIndex * transform->height;

        dst.w = transform->width * transform->scale;
        dst.h = transform->height * transform->scale;
        dst.x = static_cast<int>(transform->position.x);
        dst.y = static_cast<int>(transform->position.y);
    }

    void draw() override
    {
        TextureManager::draw(texture, src, dst, spriteFlip);
    }

    void play(const char *animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};