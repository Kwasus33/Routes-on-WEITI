#include "path.hpp"

#include "config.hpp"
#include "iostream"

Path::Path()
{
    for(int i = config::MIN_FLOOR; i <= config::MAX_FLOOR; ++i)
    {
        pointsByFloor[i] = std::vector<SDL_Point>();
    }
}

void Path::SetFromGraph(Graph* graph, const std::vector<int>& nodePath)
{
    for(auto& floor : pointsByFloor)
    {
        floor.second.clear();
    }

    std::vector<Node> nodes = graph->getNodes();
    for(const auto id : nodePath)
    {
        Node node = nodes[id];
        SDL_Point point = {node.getX(), node.getY()};
        pointsByFloor[node.getFloor()].push_back(point);
    }
}