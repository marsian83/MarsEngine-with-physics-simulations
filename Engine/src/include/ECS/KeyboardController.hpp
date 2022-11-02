#pragma once

#include "Engine.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Engine::event.type == SDL_KEYDOWN)
        {
            switch (Engine::event.key.keysym.sym)
            {
            case SDLK_w:
                sprite->play("Walk");
                transform->velocity.y = -1;
                break;

            case SDLK_a:
                sprite->play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                transform->velocity.x = -1;
                break;

            case SDLK_s:
                sprite->play("Walk");
                transform->velocity.y = 1;
                break;

            case SDLK_d:
                sprite->play("Walk");
                transform->velocity.x = 1;
                break;

            default:
                break;
            }
        }

        if (Engine::event.type == SDL_KEYUP)
        {

            switch (Engine::event.key.keysym.sym)
            {
            case SDLK_w:
                sprite->play("Idle");
                transform->velocity.y = 0;
                break;

            case SDLK_a:
                sprite->play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE;
                transform->velocity.x = 0;
                break;

            case SDLK_s:
                sprite->play("Idle");
                transform->velocity.y = 0;
                break;

            case SDLK_d:
                sprite->play("Idle");
                transform->velocity.x = 0;
                break;

            default:
                break;
            }
        }
    }
};