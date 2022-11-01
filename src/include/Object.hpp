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

public:
    Object(Group mGroup, int x, int y, const char *spritePath);
    Object(int x, int y, const char *spritePath);
    Object(Group mGroup, int x, int y, const char *spritePath, bool animated);
    Object(int x, int y, const char *spritePath, bool animated);
    ~Object();

    void init(Group mGroup, int x, int y, const char *spritePath, bool animated);

    ColliderComponent getCollider() { return entity.getComponent<ColliderComponent>(); }
    void setCollider(const char *tag);
    bool checkCollision(const char *type, Object o);
    bool checkCollision(const char *type, const char *tag);
    bool checkCollision(const char *type, ColliderComponent c);

    void setKeyboardController();

    Vector2D getPosition();
    float getX();
    float getY();
    void setPosition(int x, int y);

    float getWidth(){return transform->width;}
    float getHeight(){return transform->height;}

    float getScale(){return transform->scale;}
    void setScale(float scale);

    float distanceTo(Object o);
    float distanceToPoint(float x, float y);

    float getSpeed() { return transform->speed; }
    void setSpeed(float speed);

    Vector2D getVelocity() { return transform->velocity; }
    void setVelocity(float Vx, float Vy);
    void setVelocity(Vector2D velocity);

};