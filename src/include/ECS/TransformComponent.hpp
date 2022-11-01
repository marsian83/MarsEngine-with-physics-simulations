#pragma once

#include "Components.hpp"
#include "Vector2D.hpp"

class TransformComponent : public Component
{
private:
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32, width = 32;
    float scale = 1;

    int speed = 1;

    TransformComponent()
    {
        position.Zero();
    }

    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    TransformComponent(float s) : scale(s)
    {
        position.Zero();
    }

    TransformComponent(float x, float y, int h, int w, float s) : height(h), width(w), scale(s)
    {
        position.x = x;
        position.y = y;
    }

    void init() override
    {
        velocity.Zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

    void setPos(int x, int y)
    {
        position.x = x;
        position.y = y;
    }
};