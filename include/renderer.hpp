#pragma once

#include "SDL.h"
#include "resource_manager.hpp"

class ResourceManager;

class Renderer
{
    SDL_Window* window;
    SDL_Renderer* renderer;
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