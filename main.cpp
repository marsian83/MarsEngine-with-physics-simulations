#include "Engine.hpp"
#include "Object.hpp"

#include "Collision.hpp"

#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define G 13
#define g 0.09
#define COR 0.9

Engine *engine = nullptr;

float distance(int x1, int y1, int x2, int y2);
int signum(float n);
int randintRange(int l, int r);

class PhysicalEntity;
class InelasticEntity;
class GravitationalEntity;
class Attractor;
class CustomEntity;

std::vector<PhysicalEntity *> physicalEntities;
std::vector<InelasticEntity *> inelasticEntities;
std::vector<GravitationalEntity *> gravitationalEntities;
std::vector<Attractor *> attractors;
std::vector<CustomEntity *> customentities;

class PhysicalEntity : public Object
{
private:
    float mass = 1;
    Vector2D force;
    Vector2D acceleration;

public:
    PhysicalEntity(int x, int y, char *spritePath) : Object(x, y, spritePath)
    {
        physicalEntities.push_back(this);
    }

    void update()
    {
        this->setAcceleration(force.x / mass, force.y / mass);
        this->setVelocity(this->getVelocity().x + acceleration.x, this->getVelocity().y + acceleration.y);
    }

    float getMass() { return mass; }
    void setMass(float m) { mass = m; }
    void setMassAndScale(float m)
    {
        mass = m;
        setScale(1 + (m / 10));
    }

    Vector2D getForce() { return force; }
    void setForce(float x, float y)
    {
        force.x = x;
        force.y = y;
    }
    void addForce(float x, float y)
    {
        force.x += x;
        force.y += y;
    }

    void setForce(Vector2D f)
    {
        force = f;
    }

    Vector2D getAcceleration() { return acceleration; }
    void setAcceleration(float x, float y)
    {
        acceleration.x = x;
        acceleration.y = y;
    }
};

class InelasticEntity : public PhysicalEntity
{
public:
    InelasticEntity(int x, int y, char *spritePath) : PhysicalEntity(x, y, spritePath)
    {
        inelasticEntities.push_back(this);
        this->setCollider("inelastic-entity");
    }

    void update()
    {
        for (auto &e : inelasticEntities)
        {
            if (e != this)
            {
                float MXself = this->getX() + this->getWidth() + this->getVelocity().x + (this->getForce().x / this->getMass());
                float MYself = this->getY() + this->getHeight() + this->getVelocity().y + (this->getForce().y / this->getMass());
                float MXother = e->getX() + e->getWidth() + e->getVelocity().x + (e->getForce().x / e->getMass());
                float MYother = e->getY() + e->getHeight() + e->getVelocity().y + (e->getForce().y / e->getMass());

                if ((MXself >= MXother - e->getWidth()) && (MXother >= MXself - this->getWidth()) && (MYself >= MYother - e->getHeight()) && (MYother >= MYself - this->getHeight()))
                // if (Collision::AABB(this->getCollider(), e->getCollider()))
                {
                    float totalMass = this->getMass() + e->getMass();
                    float delVx = this->getVelocity().x - e->getVelocity().x;
                    float delVy = this->getVelocity().y - e->getVelocity().y;
                    //(Vself - Vother)(Mother/Mtotal)
                    this->setVelocity(delVx * (e->getMass() / totalMass), delVy * (e->getMass() / totalMass));
                    e->setVelocity(delVx * (this->getMass() / totalMass), delVy * (this->getMass() / totalMass));
                }
            }
        }
    }
};

class GravitationalEntity : public PhysicalEntity
{
public:
    GravitationalEntity(int x, int y, char *spritePath) : PhysicalEntity(x, y, spritePath)
    {
        gravitationalEntities.push_back(this);
        this->setCollider("gravitational-entity");
    }

    void update()
    {
        PhysicalEntity::update();
        this->setForce(0, 0);
        for (auto &e : gravitationalEntities)
        {
            if (this != e)
            {
                float numerator = G * this->getMass() * e->getMass();
                float distX = e->getX() - this->getX();
                float distY = e->getY() - this->getY();
                float dist = sqrt(pow(distX, 2) + pow(distY, 2));
                float forceMag = numerator / (pow(dist, 2));

                if ((!Collision::AABB(this->getCollider(), e->getCollider())))
                {
                    if (abs(dist) > 1)
                    {
                        float Fx = forceMag * (distX / dist);
                        float Fy = forceMag * (distY / dist);
                        this->addForce(Fx, Fy);
                    }
                }

                float MXself = this->getX() + this->getWidth() / 2 + this->getVelocity().x + (this->getForce().x / this->getMass());
                float MYself = this->getY() + this->getHeight() / 2 + this->getVelocity().y + (this->getForce().y / this->getMass());
                float MXother = e->getX() + e->getWidth() / 2 + e->getVelocity().x + (e->getForce().x / e->getMass());
                float MYother = e->getY() + e->getHeight() / 2 + e->getVelocity().y + (e->getForce().y / e->getMass());

                float distance = sqrt(pow(MXself - MXother, 2) + pow(MYself - MYother, 2));
                // if (Collision::Circle(this->getCollider(), e->getCollider()))
                // if ((MXself >= MXother - e->getWidth()) && (MXother >= MXself - this->getWidth()) && (MYself >= MYother - e->getHeight()) && (MYother >= MYself - this->getHeight()))
                if (false and distance <= this->getWidth() / 2 + e->getWidth() / 2)
                {
                    float selfVx = (this->getVelocity().x * this->getMass() + e->getVelocity().x * e->getMass() + e->getMass() * COR * (e->getVelocity().x - this->getVelocity().x)) / (this->getMass() + e->getMass());
                    float selfVy = (this->getVelocity().y * this->getMass() + e->getVelocity().y * e->getMass() + e->getMass() * COR * (e->getVelocity().y - this->getVelocity().y)) / (this->getMass() + e->getMass());
                    float otherVx = (e->getVelocity().x * e->getMass() + this->getVelocity().x * this->getMass() + this->getMass() * COR * (this->getVelocity().x - e->getVelocity().x)) / (e->getMass() + this->getMass());
                    float otherVy = (e->getVelocity().y * e->getMass() + this->getVelocity().y * this->getMass() + this->getMass() * COR * (this->getVelocity().y - e->getVelocity().y)) / (e->getMass() + this->getMass());
                    this->setVelocity(selfVx, selfVy);
                    e->setVelocity(otherVx, otherVy);
                }
            }
        }
    }
};

class Attractor : public PhysicalEntity
{
public:
    Attractor(int x, int y, char *spritePath) : PhysicalEntity(x, y, spritePath)
    {
        attractors.push_back(this);
        this->setCollider("attractor");
    }

    void update()
    {
        PhysicalEntity::update();
        for (auto &e : gravitationalEntities)
        {
            float numerator = G * this->getMass() * e->getMass();
            float distX = this->getX() - e->getX();
            float distY = this->getY() - e->getY();
            float dist = sqrt(pow(distX, 2) + pow(distY, 2));
            float forceMag = numerator / (pow(dist, 2));

            if (abs(dist) > 0)
            {
                float Fx = forceMag * (distX / dist);
                float Fy = forceMag * (distY / dist);
                e->addForce(Fx, Fy);
            }
        }
    }
};

class RigidBody : public GravitationalEntity, public InelasticEntity
{

public:
    RigidBody(int x, int y, char *spritePath) : InelasticEntity(x, y, spritePath), GravitationalEntity(x, y, spritePath)
    {
        this->GravitationalEntity::setCollider("rigid-body");
    }
};

class CustomEntity : public PhysicalEntity
{
private:
    bool gravitation = false, inelasticity = false, gravity = false, wallcollisions = false;
    float wallDampening = 0.75, groundFriction = 0;

public:
    CustomEntity(int x, int y, char *spritePath) : PhysicalEntity(x, y, spritePath)
    {
        customentities.push_back(this);
        this->setCollider("custom-entity");
    }

    void toggleGravitation() { gravitation = !gravitation; }
    void toggleInelasticity() { inelasticity = !inelasticity; }
    void toggleGravity() { gravity = !gravity; }
    void toggleWallcollisions() { wallcollisions = !wallcollisions; }

    float getWallDampening() { return wallDampening; }
    void setWallDampening(float e) { wallDampening = e; }

    float getGroundFriction() { return groundFriction; }
    void setGroundFriction(float u) { groundFriction = u; }

    void update()
    {

        PhysicalEntity::update();
        if (this->gravitation)
            this->setForce(0, 0);

        if (this->gravity)
        {
            this->setForce(0, this->getMass() * g);
        }

        if (this->wallcollisions)
        {
            float MXself = this->getX() + this->getWidth() + this->getVelocity().x + (this->getForce().x / this->getMass());
            float MYself = this->getY() + this->getHeight() + this->getVelocity().y + (this->getForce().y / this->getMass());
            if (MXself - this->getWidth() < 0)
            {
                this->setVelocity(Vector2D(-floor(wallDampening * this->getVelocity().x), this->getVelocity().y));
            }
            if (MXself > SCREEN_WIDTH)
            {
                this->setVelocity(Vector2D(-floor(wallDampening * this->getVelocity().x), this->getVelocity().y));
            }
            if (MYself - this->getHeight() < 0)
            {
                this->setVelocity(Vector2D(this->getVelocity().x, -floor(wallDampening * this->getVelocity().y)));
            }
            if (MYself > SCREEN_HEIGHT)
            {
                this->setVelocity(Vector2D(this->getVelocity().x, -floor(wallDampening * this->getVelocity().y)));
            }
        }

        if (groundFriction > 0)
        {
            float MYself = this->getY() + this->getHeight() + this->getVelocity().y + (this->getForce().y / this->getMass());
            if (MYself >= SCREEN_HEIGHT-1)
            {
                this->setVelocity(Vector2D(this->getVelocity().x * (1 - groundFriction/10), this->getVelocity().y));
            }
        }

        for (auto &e : customentities)
        {
            if (this != e)
            {
                if (this->gravitation)
                {
                    float numerator = G * this->getMass() * e->getMass();
                    float distX = e->getX() - this->getX();
                    float distY = e->getY() - this->getY();
                    float dist = sqrt(pow(distX, 2) + pow(distY, 2));
                    float forceMag = numerator / (pow(dist, 2));

                    if ((!Collision::AABB(this->getCollider(), e->getCollider())))
                    {
                        if (abs(dist) > 1)
                        {
                            float Fx = forceMag * (distX / dist);
                            float Fy = forceMag * (distY / dist);
                            this->addForce(Fx, Fy);
                        }
                    }
                }
                if (this->inelasticity)
                {
                    float MXself = this->getX() + this->getWidth() / 2 + this->getVelocity().x + (this->getForce().x / this->getMass());
                    float MYself = this->getY() + this->getHeight() / 2 + this->getVelocity().y + (this->getForce().y / this->getMass());
                    float MXother = e->getX() + e->getWidth() / 2 + e->getVelocity().x + (e->getForce().x / e->getMass());
                    float MYother = e->getY() + e->getHeight() / 2 + e->getVelocity().y + (e->getForce().y / e->getMass());

                    float distance = sqrt(pow(MXself - MXother, 2) + pow(MYself - MYother, 2));
                    if (distance <= this->getWidth() / 2 + e->getWidth() / 2)
                    {
                        float selfVx = (this->getVelocity().x * this->getMass() + e->getVelocity().x * e->getMass() + e->getMass() * COR * (e->getVelocity().x - this->getVelocity().x)) / (this->getMass() + e->getMass());
                        float selfVy = (this->getVelocity().y * this->getMass() + e->getVelocity().y * e->getMass() + e->getMass() * COR * (e->getVelocity().y - this->getVelocity().y)) / (this->getMass() + e->getMass());
                        float otherVx = (e->getVelocity().x * e->getMass() + this->getVelocity().x * this->getMass() + this->getMass() * COR * (this->getVelocity().x - e->getVelocity().x)) / (e->getMass() + this->getMass());
                        float otherVy = (e->getVelocity().y * e->getMass() + this->getVelocity().y * this->getMass() + this->getMass() * COR * (this->getVelocity().y - e->getVelocity().y)) / (e->getMass() + this->getMass());
                        this->setVelocity(selfVx, selfVy);
                        e->setVelocity(otherVx, otherVy);
                    }
                }
            }
        }
    }
};

void update()
{
    for (auto &e : physicalEntities)
    {
        e->update();
    }
    for (auto &e : inelasticEntities)
    {
        e->update();
    }
    for (auto &e : gravitationalEntities)
    {
        e->update();
    }
    for (auto &e : attractors)
    {
        e->update();
    }
    for (auto &e : customentities)
    {
        e->update();
    }
}

int main(int argv, char **args)
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    engine = new Engine();
    engine->init("MarsPhysics - simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    float r, rx, ry, m1;
    float vi = 3.3;
    r = randintRange(100, 150);
    rx = randintRange(-r, r);
    ry = signum(randintRange(-1, 1)) * ((sqrt(r * r - rx * rx)));
    GravitationalEntity(SCREEN_WIDTH / 2 + rx, SCREEN_HEIGHT / 2 + ry, "res/images/white-circle.png").setVelocity(Vector2D(rx, ry).perpendicularUnit() * vi * signum(ry));
    
    InelasticEntity(200,300,"res/images/white-circle.png").setVelocity(1,0);
    InelasticEntity(700,310,"res/images/white-circle.png").setVelocity(-1,0);

    // CustomEntity c(300, 300, "res/images/hammer.png");
    // c.setVelocity(1, 0);
    // c.setGroundFriction(0.2);
    // c.toggleGravity();
    // c.toggleWallcollisions();
    // c.toggleInelasticity();
    // CustomEntity a(390, 300, "res/images/hammer.png");
    // a.setVelocity(2, 0);
    // a.toggleGravity();
    // a.setGroundFriction(0.1);
    // a.toggleWallcollisions();
    // a.toggleInelasticity();
    // CustomEntity z(490, 300, "res/images/hammer.png");
    // z.setVelocity(2, 0);
    // z.toggleGravity();
    // z.toggleWallcollisions();
    // z.setGroundFriction(1);
    // z.toggleInelasticity();

    SDL_Rect testrect;
    testrect.x = testrect.y = 0;
    testrect.w = testrect.h = 604;

    while (engine->isRunning())
    {
        frameStart = SDL_GetTicks();

        update();

        engine->handleEvents();
        engine->update();
        engine->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    engine->clean();

    return 0;
}

float distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int signum(float n)
{
    return n < 0 ? -1 : 1;
}

int randintRange(int l, int r)
{
    return l + (std::rand() % (r - l + 1));
}