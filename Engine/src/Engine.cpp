#include "Engine.hpp"

#include <iostream>

#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"

#include "Object.hpp"

SDL_Renderer *Engine::renderer = nullptr;
SDL_Event Engine::event;
Manager Engine::manager;

std::vector<ColliderComponent *> Engine::colliders;
std::vector<Entity *> Engine::entities;

Engine::Engine()
{
}

Engine::~Engine() {}

void Engine::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Failed; SDL Error : " << SDL_GetError() << "\n";

        engineRunning = false;
    }
    else
    {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (!window)
        {
            std::cout << "SDL_CreateWindow Failed; SDL Error : " << SDL_GetError() << "\n";
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (!renderer)
        {
            std::cout << "SDL_CreateRenderer Failed; SDL Error : " << SDL_GetError() << "\n";
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        engineRunning = true;
    }
}

void Engine::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        engineRunning = false;
        break;

    default:
        break;
    }
}

void Engine::update()
{
    manager.refresh();
    manager.update();
}

void Engine::render()
{
    SDL_RenderClear(renderer);
    // render

    for (auto &e : entities)
    {
        e->draw();
    }

    // present the state of renderer
    SDL_RenderPresent(renderer);
}

void Engine::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Engine Cleaned"
              << "\n";
}

bool Engine::isRunning() { return engineRunning; }