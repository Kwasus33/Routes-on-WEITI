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
    void Render(ResourceManager* resourceManager, const int currentFloor);
    SDL_Renderer* GetSdlRenderer() const { return renderer; }
    void HideWindow() { SDL_HideWindow(window); }
    void ShowWindow() { SDL_ShowWindow(window); }
private:
    void AddFloorToRender(Floor flr);
    void AddPathToRender(Path pth, const int currentFloor);
};