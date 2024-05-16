#pragma once

#include "SDL.h"
#include "graph.hpp"
#include <map>

class ProgramManager
{
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Graph* graph;
    bool isRunning = true;
    std::map<int, SDL_Texture*> floorTextures;
    int viewedFloor = 0;
    const int MAX_FLOOR = 1;
    const int MIN_FLOOR = -1;
public:
    ProgramManager(const int screenWidth, const int screenHeight, Graph* graph);
    ~ProgramManager();
    
    void Init();
    void ProcessInput();
    void Update();
    void Render();
    bool IsRunning() const;

private:
    void LoadFloorTexture(const int floor, const char* path);
};