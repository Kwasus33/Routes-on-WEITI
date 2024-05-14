#include <gtest/gtest.h>
#include "node.hpp"
#include "graph.hpp"
#include <vector>
#include "classroom.hpp"

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

TEST(GraphTest, TestDijkstraAlgorithm)
{
    std::vector<int> distance0 = {0, 5, __INT_MAX__, 1, 8};
    std::vector<int> distance1 = {__INT_MAX__, 0, 3};
    std::vector<int> distance2 = {__INT_MAX__, __INT_MAX__, 0};
    std::vector<int> distance3 = {__INT_MAX__, __INT_MAX__, __INT_MAX__, 0, __INT_MAX__, __INT_MAX__, __INT_MAX__, 2};
    std::vector<int> distance4 = {__INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, 0, __INT_MAX__, 1};
    std::vector<int> distance5 = {__INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, 0, __INT_MAX__, __INT_MAX__, 2};
    std::vector<int> distance6 = {__INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, 2, 0};
    std::vector<int> distance7 = {__INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, 0, __INT_MAX__, 1};
    std::vector<int> distance8 = {__INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, 0};
    std::vector<int> distance9 = {__INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__, 1, __INT_MAX__, 10, 0};
    
    Node node0(0, distance0);
    Node node1(1, distance1);
    Node node2(2, distance2);
    Node node3(3, distance3);
    Node node4(4, distance4);
    Node node5(5, distance5);
    Node node6(6, distance6);
    Node node7(7, distance7);
    Node node8(8, distance8);
    Node node9(9, distance9);

    Graph testGraph;

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

    std::string className = "131";

    Classroom class1(className);
    testGraph.getNodes()[5].addClassroom(class1);

    std::vector<int> resultDistances = {0, 5, 8, 1, 6, 7, 5, 3, 9, 4};
    std::vector<int> resultNodes = {0, 3, 7, 9, 6, 4};
    
    testGraph.findRoutes(0);

    EXPECT_EQ(resultDistances, testGraph.getNodes()[0].getDistances());
    EXPECT_EQ(resultNodes, testGraph.getRoute(0, 4));

    resultDistances = {6, 11, 14, 5, 0, 3, 1, 3, 5, 2};

    testGraph.findRoutes(4);

    EXPECT_EQ(resultDistances, testGraph.getNodes()[4].getDistances());

    std::string failedSearch = "132";

    EXPECT_EQ(testGraph.findClassroom(className), 5);
    EXPECT_EQ(testGraph.findClassroom(failedSearch), -1);

}