#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "jsonReader.hpp"
#include "csvReader.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <stdexcept>

// using ::testing::_;
// using ::testing::Return;
// using ::testing::Throw;

class MockFileReader : public FileReader
{
public:
    MockFileReader() : FileReader() {}
    MockFileReader(const std::vector<std::string>& pathsVec) : FileReader(pathsVec) {}

    MOCK_METHOD(Graph, ReadDataIntoGraph, (), (const, override));
    MOCK_METHOD(nlohmann::json, LoadFromFile, (const std::string& path), (const));
};

TEST(JsonReaderTest, ReadValidJson) {
    MockFileReader mockReader({ "dummy_path" });
    nlohmann::json jsonData = {
        { "ID", 0 },
        { "X", 80 },
        { "Y", 270 },
        { "floor", 0 },
        { "distances", { 5, 8, 1 } },
        { "connected", { 1, 4, 3 } },
        { "classrooms", { 
            { { "name", "01" }, { "description", "PIPR" } },
            { { "name", "02" }, { "description", "PTCY" } }
        } }
    };

    EXPECT_CALL(mockReader, LoadFromFile("dummy_path")).WillOnce(::testing::Return(jsonData));

    Graph graph = mockReader.ReadDataIntoGraph();

    ASSERT_EQ(graph.getNodes().size(), 1);
    Node node = graph.getNodes().at(0);

    EXPECT_EQ(node.getID(), 0);
    EXPECT_EQ(node.getX(), 80);
    EXPECT_EQ(node.getY(), 270);
    EXPECT_EQ(node.getFloor(), 0);
    EXPECT_EQ(node.getDistances(), std::vector<int>({5, 8, 1}));
    EXPECT_EQ(node.getNextNodes(), std::vector<int>({1, 4, 3}));
    EXPECT_EQ(node.getClassrooms().size(), 2);
    EXPECT_EQ(node.getClassrooms().at(0).getName(), "01");
    EXPECT_EQ(node.getClassrooms().at(0).getDescription(), "PIPR");
    EXPECT_EQ(node.getClassrooms().at(1).getName(), "02");
    EXPECT_EQ(node.getClassrooms().at(1).getDescription(), "PTCY");
}

TEST(JsonReaderTest, ReadInvalidPath) {
    MockFileReader mockReader({ "invalid_path" });

    EXPECT_CALL(mockReader, LoadFromFile("invalid_path")).WillOnce(::testing::Throw(std::runtime_error("Failed to open file")));

    EXPECT_THROW({ mockReader.ReadDataIntoGraph();}, std::runtime_error);
}

TEST(JsonReaderTest, HandleInvalidJson) {
    MockFileReader mockReader({ "dummy_path" });

    EXPECT_CALL(mockReader, LoadFromFile("dummy_path")).WillOnce(::testing::Return(nlohmann::json::parse("{ invalid json }", nullptr, false)));

    EXPECT_THROW({mockReader.ReadDataIntoGraph();}, nlohmann::json::parse_error);
}


//  ############################## CSV READER TESTS ##############################

// class MockCsvReader : public csvReader {
// public:
//     MockCsvReader() : csvReader() {}
//     MockCsvReader(const std::vector<std::string>& pathsVec) : csvReader(pathsVec) {}

//     MOCK_METHOD(Node, addNode, (const std::string& line1, const std::string& line2, const std::string& line3), (const, override));
//     MOCK_METHOD(void, isReadPathValid, (const std::ifstream& fp), (const, override));
//     MOCK_METHOD(Node, createNode, (const std::string& line1, const std::string& line2), (const, override));
//     MOCK_METHOD(void, createClassrooms, (const std::string& line3, Node& node), (const, override));
// };

// TEST(CsvReaderTest, ReadValidCsv) {
//     MockCsvReader mockReader({ "dummy_path" });

//     EXPECT_CALL(mockReader, isReadPathValid(::testing::_)).Times(1);

//     // Mocking valid CSV lines
//     EXPECT_CALL(mockReader, addNode(::testing::_, ::testing::_, ::testing::_)).WillRepeatedly(
//         ::testing::Return(Node(0, std::vector<int>({ 5, 8, 1 }), std::vector<int>({ 1, 4, 3 }), 0, 80, 270))
//         );

//     Graph graph = mockReader.ReadDataIntoGraph();

//     ASSERT_EQ(graph.getNodes().size(), 0); // Since we return an empty node
// }

// TEST(CsvReaderTest, ReadInvalidPath) {
//     MockCsvReader mockReader({ "invalid_path" });

//     EXPECT_CALL(mockReader, isReadPathValid(::testing::_)).WillOnce(::testing::Throw(std::runtime_error("Failed to open file")));

//     EXPECT_THROW({
//         mockReader.ReadDataIntoGraph();
//     }, std::runtime_error);
// }

// TEST(CsvReaderTest, HandleInvalidCsv) {
//     MockCsvReader mockReader({ "dummy_path" });

//     EXPECT_CALL(mockReader, isReadPathValid(testing::_)).Times(1);

//     // Mocking invalid CSV lines
//     EXPECT_CALL(mockReader, addNode(::testing::_, ::testing::_, ::testing::_)).WillRepeatedly(::testing::Throw(std::invalid_argument("Invalid CSV format")));

//     EXPECT_THROW({
//         mockReader.ReadDataIntoGraph();
//     }, std::invalid_argument);
// }
