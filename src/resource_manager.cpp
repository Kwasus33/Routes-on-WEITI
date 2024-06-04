#include "resource_manager.hpp"

#include "iostream"
#include "config.hpp"

ResourceManager::ResourceManager(Renderer* renderer)
{
    SDL_Renderer* sdlRenderer = renderer->GetSdlRenderer();

    LoadTextureFromBitmap(config::TEXTURE_PATH_PIWNICA, -1, sdlRenderer);
    LoadTextureFromBitmap(config::TEXTURE_PATH_PARTER, 0, sdlRenderer);
    LoadTextureFromBitmap(config::TEXTURE_PATH_PIERWSZE, 1, sdlRenderer);
}

void ResourceManager::LoadTextureFromBitmap(const char* filePath, const int flr, SDL_Renderer* sdlRenderer)
{
    SDL_Surface* surface = SDL_LoadBMP(filePath);
    if (surface == nullptr)
    {
        std::cerr << "Can't load image: " << filePath << std::endl;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_Rect transform = {0, 0, config::SCREEN_WIDTH, config::SCREEN_HEIGHT};
    floors.emplace(flr, Floor(texture, transform));
    SDL_FreeSurface(surface);
}