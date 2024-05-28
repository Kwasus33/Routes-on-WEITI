#include "resource_manager.hpp"

ResourceManager::ResourceManager()
{
    floors[-1] = Floor(LoadTextureFromBitmap("assets/piwnica.bmp"))
    floors[0] = Floor(LoadTextureFromBitmap("assets/parter.bmp"))
    floors[1] = Floor(LoadTextureFromBitmap("assets/pierwsze.bmp"))
}

SDL_Texture* ResourceManager::LoadTextureFromBitmap(std::string filePath)
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = SDL_LoadBMP(filePath);
    if (surface == nullptr)
    {
        std::cerr << "Can't load image: " << path << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    return texture;
}