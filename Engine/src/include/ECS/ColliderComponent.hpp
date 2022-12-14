#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "ECS.hpp"
#include "Components.hpp"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;

    TransformComponent *transform;

    ColliderComponent(){}

    void init() override
    {
        if (!(entity->hasComponent<TransformComponent>()))
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        Engine::colliders.push_back(this);
    }

    void update() override
    {
        collider.x = (int)transform->position.x;
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};