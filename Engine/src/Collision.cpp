#include <math.h>
#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB)
{
    return (rectA.x + rectA.w >= rectB.x && rectB.x + rectB.w >= rectA.x &&
            rectA.y + rectA.h >= rectB.y && rectB.y + rectB.h >= rectA.y);
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
    return (AABB(colA.collider, colB.collider));
}

bool Collision::Circle(const ColliderComponent &A, const ColliderComponent &B)
{
    // if ((A.collider.w != A.collider.h) || (B.collider.w != B.collider.h))
    // {
    //     throw("The given collider components to Collision::Circle are not of circles");
    // }
    Vector2D C1(A.collider.x + ((A.collider.w) / 2), A.collider.y + ((A.collider.h) / 2));
    Vector2D C2(B.collider.x + ((B.collider.w) / 2), B.collider.y + ((B.collider.h) / 2));
    float dist = sqrt(pow(C1.x - C2.x, 2) + pow(C1.y - C2.y, 2));
    return (dist <= A.collider.w);
}