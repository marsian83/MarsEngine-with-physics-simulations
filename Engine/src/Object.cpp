#include "Object.hpp"
#include "Engine.hpp"
#include "Collision.hpp"

#include <math.h>

Object::Object(Group mGroup, int x, int y, const char *spritePath)
{
    init(mGroup, x, y, spritePath, false);
}

Object::Object(int x, int y, const char *spritePath)
{
    init(Engine::default_group, x, y, spritePath, false);
}

Object::Object(Group mGroup, int x, int y, const char *spritePath, bool animated)
{
    init(mGroup, x, y, spritePath, animated);
}

Object::Object(int x, int y, const char *spritePath, bool animated)
{
    init(Engine::default_group, x, y, spritePath, animated);
}

void Object::init(Group mGroup, int x, int y, const char *spritePath, bool animated)
{
    entity.addComponent<TransformComponent>(x, y);
    entity.addComponent<SpriteComponent>(spritePath, animated);
    entity.addGroup(mGroup);
    transform = &entity.getComponent<TransformComponent>();
    sprite = &entity.getComponent<SpriteComponent>();
}

Object::~Object() {}

void Object::setCollider(const char *tag)
{
    entity.addComponent<ColliderComponent>(tag);
}

bool Object::checkCollision(const char *type, Object o)
{
    if (type == "AABB")
    {
        return (Collision::AABB(this->getCollider(), o.getCollider()));
    }
}

bool Object::checkCollision(const char *type, const char *tag)
{
    if (type == "AABB")
    {

        for (auto c : Engine::colliders)
        {
            if (c->tag == entity.getComponent<ColliderComponent>().tag)
            {
                continue;
            }
            if (Collision::AABB(entity.getComponent<ColliderComponent>(), *c))
            {
                if (c->tag == tag)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Object::checkCollision(const char *type, ColliderComponent c)
{
    if (type == "AABB")
    {
        return (Collision::AABB(this->getCollider(), c));
    }
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

void Object::setKeyboardController()
{
    entity.addComponent<KeyboardController>();
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