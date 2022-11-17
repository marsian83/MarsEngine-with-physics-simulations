#pragma once

#include <SDL2/SDL.h>

#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"

class Object
{
private:
    Entity &entity = Engine::manager.addEntity();
    TransformComponent *transform;
    SpriteComponent *sprite;
    void init(int x, int y, const char *spritePath);

public:
    Object(int x, int y, const char *spritePath);
    ~Object();


    ColliderComponent getCollider() { return entity.getComponent<ColliderComponent>(); }
    void setCollider(const char *tag);

    // void setKeyboardController();

    Vector2D getPosition();
    float getX();
    float getY();
    void setPosition(int x, int y);

    float getWidth() { return transform->width * transform->scale; }
    float getHeight() { return transform->height * transform->scale; }

    float getScale() { return transform->scale; }
    void setScale(float scale);

    float distanceTo(Object o);
    float distanceToPoint(float x, float y);

    float getSpeed() { return transform->speed; }
    void setSpeed(float speed);

    Vector2D getVelocity() { return transform->velocity; }
    void setVelocity(float Vx, float Vy);
    void setVelocity(Vector2D velocity);
};