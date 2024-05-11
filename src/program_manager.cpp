#include "program_manager.hpp"

#include <iostream>

ProgramManager::ProgramManager(int screenWidth, int screenHeight) 
    : screenWidth{screenWidth}, screenHeight{screenHeight}, isRunning{true}
{
    // Setup window
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
    SDL_RenderClear(renderer);
}

ProgramManager::~ProgramManager() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ProgramManager::Init()
{
    // Load Floors
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect transform{0, 0, 32, 32};

    surface = SDL_LoadBMP("assets/greenland_grid_velo.bmp");
    if(surface == nullptr) 
    {
        std::cerr << "Can't load image" << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    floors[-1] = Floor(texture, transform);

    surface = SDL_LoadBMP("assets/dots.bmp");
    if(surface == nullptr) 
    {
        std::cerr << "Can't load image" << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    transform.y = 100;
    floors[0] = Floor(texture, transform);

    SDL_FreeSurface(surface);
}

void ProgramManager::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT) 
        {
            isRunning = false;
        } 
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) 
        {
            isRunning = false;
        }
    }
}

void ProgramManager::Update()
{
    return;
}

void ProgramManager::Render()
{
    SDL_RenderClear(renderer);
    
    for(const auto& flr : floors)
    {
        SDL_RenderCopy(renderer, flr.second.texture, NULL, &flr.second.transform);
    }

    SDL_RenderPresent(renderer);
}

bool ProgramManager::IsRunning()
{
    return isRunning;
}