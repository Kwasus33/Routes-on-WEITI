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

    // Load Textures
    SDL_Surface* tmpSurface;
    tmpSurface = IMG_Load("assets/Coyote_skeleton.png");
    if(tmpSurface == nullptr) 
    {
        std::cerr << "Can't load image" << std::endl;
        return;
    }
    floors[-1] = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    tmpSurface = IMG_Load("assets/Capture.PNG");
    if(tmpSurface == nullptr) 
    {
        std::cerr << "Can't load image" << std::endl;
        return;
    }
    floors[0] = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

ProgramManager::~ProgramManager() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

    // SDL_RenderCopy(renderer, floors[-1], NULL, NULL);

    SDL_RenderPresent(renderer);
}

bool ProgramManager::IsRunning()
{
    return isRunning;
}