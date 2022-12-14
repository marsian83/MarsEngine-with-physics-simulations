#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "ECS/ECS.hpp"

class ColliderComponent;

class Engine
{
private:
    bool engineRunning;
    SDL_Window *window;

public:
    Engine();
    ~Engine();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static Manager manager;
    static std::vector<Entity *> entities;
    static std::vector<ColliderComponent *> colliders;
};