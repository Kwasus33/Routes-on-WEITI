#include <gtest/gtest.h>
#include "node.hpp"
#include "graph.hpp"
#include <vector>
#include "classroom.hpp"

TEST(GraphTest, CreateGraph)
{
    std::vector<int> distance1 = {123};
    std::vector<int> connected1 = {1};
    std::vector<int> distance2 = {123, 24, 12};
    std::vector<int> connected2 = {0, 3, 5};
    std::vector<int> distance3;
    std::vector<int> connected3;
    std::vector<int> empty;
    Node node1(0, distance1, connected1, 0, 0, 0);
    Node node2(1, distance2, connected2, 0, 0, 0);
    Node node3(2, distance3, connected3, 0, 0, 0);
    Node node4(3, empty, empty, 0, 0, 0);
    Node node5(4, empty, empty, 0, 0, 0);
    Node node6(5, empty, empty, 0, 0, 0);
    Graph testGraph;
    testGraph.addNode(node1);
    testGraph.addNode(node2);
    testGraph.addNode(node3);
    testGraph.addNode(node4);
    testGraph.addNode(node5);
    testGraph.addNode(node6);
    std::vector<Node> nodes = testGraph.getNodes();
    std::vector<int> result1 = {0, 123, __INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__};
    std::vector<int> result2 = {123, 0, __INT_MAX__, 24, __INT_MAX__, 12};
    std::vector<int> result3 = {__INT_MAX__, __INT_MAX__, 0, __INT_MAX__, __INT_MAX__, __INT_MAX__};
    EXPECT_EQ(nodes[0].getDistances(), result1);
    EXPECT_EQ(nodes[1].getDistances(), result2);
    EXPECT_EQ(nodes[2].getDistances(), result3);
}

TEST(GraphTest, TestDijkstraAlgorithm)
{   std::vector<int> empty;
    std::vector<int> distance0 = {5, 1, 8};
    std::vector<int> connected0 = {1, 3, 4};
    std::vector<int> distance1 = {3};
    std::vector<int> connected1 = {2};
    std::vector<int> distance2;
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

    Node node0(0, distance0, connected0, 0, 0, 0);
    Node node1(1, distance1, connected1, 0, 0, 0);
    Node node2(2, distance2, empty, 0, 0, 0);
    Node node3(3, distance3, connected3, 0, 0, 0);
    Node node4(4, distance4, connected4, 0, 0, 0);
    Node node5(5, distance5, connected5, 0, 0, 0);
    Node node6(6, distance6, connected6, 0, 0, 0);
    Node node7(7, distance7, connected7, 0, 0, 0);
    Node node8(8, distance8, empty, 0, 0, 0);
    Node node9(9, distance9, connected9, 0, 0, 0);

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