#pragma once

#include "SDL.h"
#include "resource_manager.hpp"

class Renderer
{
    int windowWidth, windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    Renderer(int windowWidth, int windoHeight);
    void Render(const ResourceManager* resourceManager);
    SDL_Renderer* GetSdlRenderer() const { return renderer; }
private:
    void AddFloorToRender(Floor flr);
    void AddPathToRender(Path pth);
};