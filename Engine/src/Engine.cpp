#include "Engine.hpp"

#include <iostream>

#include "TextureManager.hpp"
#include "Map.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"

#include "Object.hpp"

Map *map;
SDL_Renderer *Engine::renderer = nullptr;
SDL_Event Engine::event;
Manager Engine::manager;

std::vector<ColliderComponent *> Engine::colliders;

enum groupLabels : std::size_t
{
    groupBG,
    groupMap,
    groupDefault,
    Layer1,
    Layer2,
    Layer3,
    Layer4,
    Layer5,
    LayerHUD,
};

Group Engine::default_group = groupDefault;

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
    map = new Map();
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

auto &bg(Engine::manager.getGroup(groupBG));
auto &maplayer(Engine::manager.getGroup(groupMap));
auto &defaultgroup(Engine::manager.getGroup(groupDefault));
auto &layer(Engine::manager.getGroup(Layer1));
auto &layer2(Engine::manager.getGroup(Layer2));
auto &layer3(Engine::manager.getGroup(Layer3));
auto &layer4(Engine::manager.getGroup(Layer4));
auto &layer5(Engine::manager.getGroup(Layer5));
auto &HUD(Engine::manager.getGroup(LayerHUD));

void Engine::render()
{
    SDL_RenderClear(renderer);
    // render
    for (auto &t : bg)
    {
        t->draw();
    }
    for (auto &e : maplayer)
    {
        e->draw();
    }
    for (auto &p : defaultgroup)
    {
        p->draw();
    }
    for (auto &e : HUD)
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

void Engine::AddTile(int id, int x, int y)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(groupMap);
}

bool isRunning();