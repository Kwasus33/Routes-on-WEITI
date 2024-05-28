#include "resource_manager.hpp"

#include "iostream"

ResourceManager::ResourceManager(SDL_Renderer* sdlRenderer)
{
    SDL_Texture* tex;
    tex = LoadTextureFromBitmap("../assets/piwnica.bmp", sdlRenderer);
    floors[-1] = Floor(tex);
    tex = LoadTextureFromBitmap("../assets/parter.bmp", sdlRenderer);
    floors[0] = Floor(tex);
    tex = LoadTextureFromBitmap("../assets/pierwsze.bmp", sdlRenderer);
    floors[1] = Floor(tex);
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