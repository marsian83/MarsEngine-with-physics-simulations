#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component
{
private:
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;

    int tileID;
    char *path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID)
        {
        case 0:
            path = "res/images/tile0.jpg";
            break;
        case 1:
            path = "res/images/tile1.jpg";
            break;
        case 2:
            path = "res/images/tile2.jpg";
            break;

        default:
            break;
        }
    }

    void init() override
    {
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};