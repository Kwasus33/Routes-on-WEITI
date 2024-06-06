#include "renderer.hpp"

#include "iostream"
#include "config.hpp"

Renderer::Renderer()
{
    // Setup window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error(std::string("SDL initialization failed: ") + SDL_GetError());
    }
    window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(SDL_CreateWindow(
        "Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        config::SCREEN_WIDTH, config::SCREEN_HEIGHT, SDL_WINDOW_HIDDEN));
    if (!window)
    {
        throw std::runtime_error(std::string("Window initialization failed: ") + SDL_GetError());
    }

    // Setup SDL renderer
    renderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(SDL_CreateRenderer(
        window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!renderer)
    {
        throw std::runtime_error(std::string("Renderer initialization failed: ") + SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 200, 255);
    SDL_RenderClear(renderer.get());
}

SDL_Renderer *Renderer::getSdlRenderer() const
{
    return renderer.get();
}

void Renderer::hideWindow() const
{
    SDL_HideWindow(window.get());
}

void Renderer::showWindow() const
{
    SDL_ShowWindow(window.get());
}

void Renderer::render(const ResourceManager *resourceManager, const int currentFloor) const
{
    SDL_RenderClear(renderer.get());

    // Draw current floor
    const Floor &floorObject = resourceManager->getFloor(currentFloor);
    addFloorToRender(floorObject);

    // Draw path on current floor
    addPathToRender(resourceManager->getPath(), currentFloor);

    SDL_RenderPresent(renderer.get());
}

void Renderer::addFloorToRender(const Floor &flr) const
{
    auto transformedFloor = flr.GetTransfrom();
    SDL_Texture *tex = flr.GetTexture();
    SDL_RenderCopy(renderer.get(), tex, NULL, &transformedFloor);
}

void Renderer::addPathToRender(const MapPath &pth, const int currentFloor) const
{
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    auto points = pth.getPointsOnFloor(currentFloor);
    int pointsSizeCasted = static_cast<int>(points.size());
    for (int i = 1; i < pointsSizeCasted; i++)
    {
        auto point1 = points[i - 1];
        auto point2 = points[i];

        SDL_RenderDrawLine(renderer.get(), point1.x, point1.y, point2.x, point2.y);
    }
}