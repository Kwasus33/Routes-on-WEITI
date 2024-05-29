#include "resource_manager.hpp"

#include "iostream"
#include "config.hpp"

ResourceManager::ResourceManager(Renderer* renderer)
{
    SDL_Renderer* sdlRenderer = renderer->GetSdlRenderer();
    SDL_Rect transform = {0, -config::SCREEN_HEIGHT, config::SCREEN_WIDTH, config::SCREEN_HEIGHT};
    SDL_Texture* tex;
    tex = LoadTextureFromBitmap(config::TEXTURE_PATH_PIWNICA, sdlRenderer);
    floors[-1] = Floor(tex, transform);

    transform.y += config::SCREEN_HEIGHT;
    tex = LoadTextureFromBitmap(config::TEXTURE_PATH_PARTER, sdlRenderer);
    floors[0] = Floor(tex, transform);

    transform.y += config::SCREEN_HEIGHT;
    tex = LoadTextureFromBitmap(config::TEXTURE_PATH_PIERWSZE, sdlRenderer);
    floors[1] = Floor(tex, transform);
}

SDL_Texture* ResourceManager::LoadTextureFromBitmap(const char* filePath, SDL_Renderer* sdlRenderer)
{
    SDL_Surface* surface = SDL_LoadBMP(filePath);
    if (surface == nullptr)
    {
        std::cerr << "Can't load image: " << filePath << std::endl;
        return SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    return texture;
}