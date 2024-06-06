#include <gtest/gtest.h>
#include "path.hpp"
#include "graph.hpp"
#include "node.hpp"
#include <memory>

TEST(PathTest, SetFromGraph) 
{
    Graph testGraph;

    std::vector<int> empty = {};
    std::vector<int> distance0 = {5, 1, 8};
    std::vector<int> connected0 = {1, 3, 4};
    std::vector<int> distance1 = {3};
    std::vector<int> connected1 = {2};
    std::vector<int> distance2 = {};
    std::vector<int> distance3 = {2};
    std::vector<int> connected3 = {7};
    std::vector<int> distance4 = {1};
    std::vector<int> connected4 = {6};
    std::vector<int> distance5 = {2};
    std::vector<int> connected5 = {8};
    std::vector<int> distance6 = {2};
    std::vector<int> connected6 = {5};
    std::vector<int> distance7 = {1};
    std::vector<int> connected7 = {9};
    std::vector<int> distance8;
    std::vector<int> distance9 = {1, 10};
    std::vector<int> connected9 = {6, 8};

    Node node0(0, distance0, connected0, 1, 1, 10);
    Node node1(1, distance1, connected1, 0, 2, 20);
    Node node2(2, distance2, empty, 0, 3, 30);
    Node node3(3, distance3, connected3, 0, 0, 0);
    Node node4(4, distance4, connected4, 0, 0, 0);
    Node node5(5, distance5, connected5, 0, 0, 0);
    Node node6(6, distance6, connected6, 0, 0, 0);
    Node node7(7, distance7, connected7, 0, 0, 0);
    Node node8(8, distance8, empty, 0, 0, 0);
    Node node9(9, distance9, connected9, 0, 0, 0);

    testGraph.addNode(node0);
    testGraph.addNode(node1);
    testGraph.addNode(node2);
    testGraph.addNode(node3);
    testGraph.addNode(node4);
    testGraph.addNode(node5);
    testGraph.addNode(node6);
    testGraph.addNode(node7);
    testGraph.addNode(node8);
    testGraph.addNode(node9);


    MapPath path;

    std::vector<int> nodePath = {0, 1, 2};

    path.setFromGraph(&testGraph, nodePath);

    EXPECT_EQ(path.getPointsOnFloor(1).size(), 1);
    EXPECT_EQ(path.getPointsOnFloor(0).size(), 2);

    EXPECT_EQ(path.getPointsOnFloor(1)[0].x, 1);
    EXPECT_EQ(path.getPointsOnFloor(1)[0].y, 10);

    EXPECT_EQ(path.getPointsOnFloor(0)[0].x, 2);
    EXPECT_EQ(path.getPointsOnFloor(0)[0].y, 20);

    EXPECT_EQ(path.getPointsOnFloor(0)[1].x, 3);
    EXPECT_EQ(path.getPointsOnFloor(0)[1].y, 30);
}
