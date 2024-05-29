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
    void Render(const ResourceManager* resourceManager);
    SDL_Renderer* GetSdlRenderer() const { return renderer; }
private:
    void AddFloorToRender(Floor flr);
    void AddPathToRender(Path pth);
};