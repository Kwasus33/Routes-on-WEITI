#pragma once

#include "SDL.h"
#include "resource_manager.hpp"

class ResourceManager;

struct SDLWindowDeleter 
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
};
struct SDLRendererDeleter 
{
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
};


class Renderer
{
    std::unique_ptr<SDL_Window,SDLWindowDeleter> window;
    std::unique_ptr<SDL_Renderer,SDLRendererDeleter> renderer;
public:
    Renderer();
    void Render(const ResourceManager* resourceManager, const int currentFloor) const;
    SDL_Renderer* GetSdlRenderer() const;
    void HideWindow() const;
    void ShowWindow() const;
private:
    void AddFloorToRender(const Floor& flr) const;
    void AddPathToRender(const Path& pth, const int currentFloor) const;
};