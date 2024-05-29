#include "path.hpp"

#include "config.hpp"

Path::Path()
{
    for(int i = config::MIN_FLOOR; i <= config::MAX_FLOOR; ++i)
    {
        pointsByFloor[i] = std::vector<SDL_Point>();
    }
}

void Path::SetFromGraph(const Graph& Graph, const std::vector<int>& nodePath)
{
    //TODO i think this is more of logic's job??
    //idk think about it
    //too eepy now
    //a mimir
}