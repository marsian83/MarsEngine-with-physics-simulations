#include "Object.hpp"
#include "Engine.hpp"
#include "Collision.hpp"

#include <math.h>

Object::Object(int x, int y, const char *spritePath)
{
    init(x, y, spritePath);
}

void Object::init(int x, int y, const char *spritePath)
{
    entity.addComponent<TransformComponent>(x, y);
    entity.addComponent<SpriteComponent>(spritePath);
    transform = &entity.getComponent<TransformComponent>();
    sprite = &entity.getComponent<SpriteComponent>();
    Engine::entities.push_back(&this->entity);
}

Object::~Object() {}

void Object::setCollider(const char *tag)
{
    entity.addComponent<ColliderComponent>(tag);
}

Vector2D Object::getPosition()
{
    return transform->position;
}

float Object::getX()
{
    return transform->position.x;
}

float Object::getY()
{
    return transform->position.y;
}

void Object::setPosition(int x, int y)
{
    transform->setPos(x, y);
}

void Object::setScale(float scale)
{
    transform->scale = scale;
}

float Object::distanceTo(Object o)
{
    return sqrt(pow(o.transform->position.x - transform->position.x, 2) + pow(o.transform->position.y - transform->position.y, 2));
}

float Object::distanceToPoint(float x, float y)
{
    return sqrt(pow(x - transform->position.x, 2) + pow(y - transform->position.y, 2));
}

void Object::setSpeed(float speed)
{
    transform->speed = speed;
}

void Object::setVelocity(float Vx, float Vy)
{
    transform->velocity.x = Vx;
    transform->velocity.y = Vy;
}

void Object::setVelocity(Vector2D velocity)
{
    transform->velocity = velocity;
}