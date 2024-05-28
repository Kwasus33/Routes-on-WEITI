#pragma once

#include "floor.hpp"
#include "path.hpp"
#include <map>
#include <string>

class ResourceManager
{
    std::map<int,Floor> floors;
public:
    void LoadTextureFromBitmap(std::string path);
};