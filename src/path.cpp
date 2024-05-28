#include "path.hpp"

#include "config.hpp"

Path::Path()
{
    for(int i = config::MIN_FLOOR; i <= config::MAX_FLOOR; ++i)
    {
        pointsByFloor[i] = std::vector<SDL_Point>();
    }
}