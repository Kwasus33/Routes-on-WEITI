#include "renderer.hpp"

#include "iostream"
#include "config.hpp"

Renderer::Renderer()
{
    // Setup window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        "Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        config::SCREEN_WIDTH, config::SCREEN_HEIGHT, SDL_WINDOW_SHOWN
        );
    if (!window)
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
    SDL_RenderClear(renderer);
}

void Renderer::Render(ResourceManager* resourceManager)
{
    SDL_RenderClear(renderer);

    for (const auto& pair : resourceManager->GetFloors())
    {
        AddFloorToRender(pair.second);
    }

    AddPathToRender(resourceManager->GetPath());

    SDL_RenderPresent(renderer);
}

void Renderer::AddFloorToRender(Floor flr)
{
    SDL_RenderCopy(renderer, flr.GetTexture(), NULL, &flr.GetTransfrom());
}

void Renderer::AddPathToRender(Path pth)
{

}