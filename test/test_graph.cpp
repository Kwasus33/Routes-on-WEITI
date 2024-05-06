#include <gtest/gtest.h>
#include "node.hpp"
#include "graph.hpp"
#include <vector>

TEST(GraphTest, CreateGraph)
{
    std::vector<int> distance1 = {0, 123, __INT_MAX__};
    std::vector<int> distance2 = {__INT_MAX__, 0, 123, 24, __INT_MAX__, 12};
    std::vector<int> distance3 = {__INT_MAX__, __INT_MAX__, 0};
    std::vector<int> dst;
    Node node1(0, distance1);
    Node node2(1, distance2);
    Node node3(2, distance3);
    Node node4(3, dst);
    Node node5(4, dst);
    Node node6(5, dst);
    Graph testGraph;
    testGraph.addNode(node1);
    testGraph.addNode(node2);
    testGraph.addNode(node3);
    testGraph.addNode(node4);
    testGraph.addNode(node5);
    testGraph.addNode(node6);
    std::vector<Node> nodes = testGraph.getNodes();
    distance1.push_back(__INT_MAX__);
    distance1.push_back(__INT_MAX__);
    distance1.push_back(__INT_MAX__);
    distance2[0] = 123;
    distance3[1] = 123;
    distance3.push_back(__INT_MAX__);
    distance3.push_back(__INT_MAX__);
    distance3.push_back(__INT_MAX__);
    EXPECT_EQ(nodes[0].getDistances(), distance1);
    EXPECT_EQ(nodes[1].getDistances(), distance2);
    EXPECT_EQ(nodes[2].getDistances(), distance3);
}