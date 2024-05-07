#include <gtest/gtest.h>
#include "node.hpp"

TEST(NodeTest, GetID)
{
    std::vector<int> distances = {1, 2, 3};
    Node node(1, distances);
    EXPECT_EQ(node.getID(), 1);
}

TEST(NodeTest, GetDistances)
{
    std::vector<int> distances = {1, 2, 3};
    Node node(1, distances);
    EXPECT_EQ(node.getDistances(), distances);
}

TEST(NodeTest, GetNextNodes)
{
    std::vector<int> distances = {1, 0, 3, __INT_MAX__};
    Node node(1, distances);
    std::vector<int> nextNodes = node.getNextNodes();
    EXPECT_EQ(nextNodes.size(), distances.size());
    std::vector<int> result = {0, 1, 2, -1};
    EXPECT_EQ(node.getNextNodes(), result);
}

TEST(NodeTest, SetDistance)
{
    std::vector<int> distances = {1, 2, 3};
    Node node(1, distances);
    node.setDistance(1, 5);
    EXPECT_EQ(node.getDistances()[1], 5);
}

TEST(NodeTest, SetNextNode)
{
    std::vector<int> distances = {1, 2, 3};
    Node node(1, distances);
    node.setNextNode(1, 2);
    EXPECT_EQ(node.getNextNodes()[1], 2);
}

TEST(NodeTest, AddRoute)
{
    std::vector<int> distances = {1, 2, 3};
    Node node(1, distances);
    node.addRoute(1, 5, 2);
    EXPECT_EQ(node.getDistances()[1], 5);
    EXPECT_EQ(node.getNextNodes()[1], 2);
}
