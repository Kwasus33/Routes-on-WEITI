#include <gtest/gtest.h>
#include "node.hpp"
#include "classroom.hpp"

TEST(NodeTest, GetID)
{
    std::vector<int> distances = {1, 2, 3};
    std::vector<int> connected = {0, 1, 2};
    Node node(1, distances, connected);
    EXPECT_EQ(node.getID(), 1);
}

TEST(NodeTest, GetDistances)
{
    std::vector<int> distances = {1, 3};
    std::vector<int> connected = {1, 3};
    Node node(0, distances, connected);
    std::vector<int> result = {0, 1, __INT_MAX__, 3};
    EXPECT_EQ(node.getDistances(), result);
}

TEST(NodeTest, GetNextNodes)
{
    std::vector<int> distances = {1, 3};
    std::vector<int> connected = {1, 3};
    Node node(0, distances, connected);
    std::vector<int> nextNodes = node.getNextNodes();
    EXPECT_EQ(nextNodes.size(), 4);
    std::vector<int> result = {0, 1, -1, 3};
    EXPECT_EQ(node.getNextNodes(), result);
}

TEST(NodeTest, SetDistance)
{
    std::vector<int> distances = {1, 2, 3};
    std::vector<int> connected = {0, 1, 2};
    Node node(1, distances, connected);
    node.setDistance(1, 5);
    EXPECT_EQ(node.getDistances()[1], 5);
}

TEST(NodeTest, SetNextNode)
{
    std::vector<int> distances = {1, 2, 3};
    std::vector<int> connected = {0, 1, 2};
    Node node(1, distances, connected);
    node.setNextNode(1, 2);
    EXPECT_EQ(node.getNextNodes()[1], 2);
}

TEST(NodeTest, AddRoute)
{
    std::vector<int> distances = {1, 2, 3};
    std::vector<int> connected = {0, 1, 2};
    Node node(1, distances, connected);
    node.addRoute(1, 5, 2);
    EXPECT_EQ(node.getDistances()[1], 5);
    EXPECT_EQ(node.getNextNodes()[1], 2);
}

TEST(NodeTest, AddClassroomm)
{
    std::vector<int> distances = {0, 1, 2};
    std::vector<int> connected = {0, 1, 2};
    Node node(0, distances, connected);
    Classroom class1("131");
    node.addClassroom(class1);

    std::string classNumber = "131";
    std::string classNumber2 = "132";

    EXPECT_TRUE(node.findClassroom(classNumber));
    EXPECT_FALSE(node.findClassroom(classNumber2));
}