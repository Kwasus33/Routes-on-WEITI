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
        config::SCREEN_WIDTH, config::SCREEN_HEIGHT, SDL_WINDOW_HIDDEN
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

void Renderer::Render(ResourceManager* resourceManager, const int currentFloor)
{
    SDL_RenderClear(renderer);

    Floor floorObject = resourceManager->GetFloor(currentFloor);
    AddFloorToRender(floorObject);

    AddPathToRender(resourceManager->GetPath(), currentFloor);

    SDL_RenderPresent(renderer);
}

void Renderer::AddFloorToRender(Floor flr)
{
    auto transformedFloor = flr.GetTransfrom();
    SDL_RenderCopy(renderer, flr.GetTexture(), NULL, &transformedFloor);
}

void Renderer::AddPathToRender(Path pth, const int currentFloor)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    auto points = pth.GetPointsOnFloor(currentFloor);
    int pointsSizeCasted = static_cast<int>(points.size());
    for (int i = 1; i < pointsSizeCasted; i++)
    {
        auto point1 = points[i - 1];
        auto point2 = points[i];

        SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);
    }
}