#include "program_manager.hpp"

#include <iostream>

ProgramManager::ProgramManager(const int screenWidth, const int screenHeight, Graph* graph) 
    : screenWidth{screenWidth}, screenHeight{screenHeight}, graph{graph}
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
    LoadFloorTexture(-1, "../assets/greenland_grid_velo.bmp");
    LoadFloorTexture(0, "../test/test_graph.bmp");
    LoadFloorTexture(1, "../assets/dots.bmp");

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
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) 
        {
            if(viewedFloor > MIN_FLOOR) viewedFloor -= 1;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) 
        {
            if(viewedFloor < MAX_FLOOR) viewedFloor += 1;
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
    
    // Render floor image
    SDL_Rect transform{0, 0, screenWidth, screenHeight};
    SDL_RenderCopy(renderer, floorTextures[viewedFloor], NULL, &transform);

    // Render path
    //todo set positions in json
    //todo get path, cache it maybe??
    //todo render path by rendering lines between nodes in path

    SDL_RenderPresent(renderer);
}

bool ProgramManager::IsRunning() const
{
    return isRunning;
}

void ProgramManager::LoadFloorTexture(const int floor, const char* path)
{
    SDL_Surface* surface;
    SDL_Texture* texture;
    surface = SDL_LoadBMP(path);
    if(surface == nullptr) 
    {
        std::cerr << "Can't load image: " << path << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    floorTextures[floor] = texture;
    
    SDL_FreeSurface(surface);
}