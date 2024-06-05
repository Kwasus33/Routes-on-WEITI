#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "jsonReader.hpp"
#include "csvReader.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <stdexcept>


// Mocking the jsonReader class by subclassing
class MockJsonReader : public jsonReader {
public:
    MOCK_CONST_METHOD1(isReadPathValid, void(const std::ifstream&));
    MOCK_CONST_METHOD1(LoadFromFile, json(const std::string&));
    MOCK_CONST_METHOD1(createNode, Node(const json&));
    MOCK_CONST_METHOD2(createClassrooms, void(const json&, Node&));
};

// Test fixture for jsonReader
class JsonReaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize mock JsonReader
        mock_json_reader = std::make_unique<MockJsonReader>();
    }

    std::unique_ptr<MockJsonReader> mock_json_reader;
};

// Test case for successful data reading
TEST_F(JsonReaderTest, ReadDataIntoGraphSuccess) {
    // Prepare test data
    json mock_json_data = {
        {
            {"ID", 100},
            {"X", 80},
            {"Y", 270},
            {"floor", 0},
            {"distances", {5, 8, 1}},
            {"connected", {1, 4, 3}},
            {"classrooms", {{"name", "01"}, {"description", "PIPR"}}, {"name", "02"}, {"description", "PTCY"}}
        }
    };
    int id = 100;
    std::vector<int> dist = {5, 8, 1};
    std::vector<int> conn = {1, 4, 3};
    int floor = 0;
    int x = 80;
    int y = 270;

    Node mock_node(id, dist, conn, floor, x, y);

    // Set expectations
    EXPECT_CALL(*mock_json_reader, isReadPathValid(testing::_));
    EXPECT_CALL(*mock_json_reader, LoadFromFile("test_file.json")).WillOnce(testing::Return(mock_json_data));
    EXPECT_CALL(*mock_json_reader, createNode(testing::_)).WillOnce(testing::Return(mock_node));
    EXPECT_CALL(*mock_json_reader, createClassrooms(testing::_, testing::_));

    // Perform the test
    Graph graph = mock_json_reader->ReadDataIntoGraph();

    // Check if graph contains expected number of nodes
    ASSERT_EQ(graph.getNodes().size(), 1);

    // Additional assertions can be added to check the correctness of the nodes and their properties
}

// Test case for file not found
TEST_F(JsonReaderTest, ReadDataIntoGraphFileNotFound) {
    // Set expectations
    EXPECT_CALL(*mock_json_reader, isReadPathValid(testing::_));
    EXPECT_CALL(*mock_json_reader, LoadFromFile("test_file.json")).WillOnce(testing::Throw(std::runtime_error("File not found")));

    // Perform the test and check if exception is thrown
    ASSERT_THROW(mock_json_reader->ReadDataIntoGraph(), std::runtime_error);
}

// Test case for invalid JSON format
TEST_F(JsonReaderTest, ReadDataIntoGraphInvalidJson) {
    // Prepare test data with invalid JSON format
    json mock_invalid_json_data = {
        {
            {"ID", 0},
            {"X", 80},
            {"Y", 270},
            {"floor", 0},
            {"distances", {5, 8, 1}},
            {"connected", {1, 4, 3}},
            {"classrooms", {{"name", "01"}, {"description", "PIPR"}}, {"name", "02"}, {"description", "PTCY"}} // Missing closing brace for classrooms array
        }
    };

    // Set expectations
    EXPECT_CALL(*mock_json_reader, isReadPathValid(testing::_));
    EXPECT_CALL(*mock_json_reader, LoadFromFile("test_file.json")).WillOnce(testing::Return(mock_invalid_json_data));

    // Perform the test and check if exception is thrown
    ASSERT_THROW(mock_json_reader->ReadDataIntoGraph(), nlohmann::detail::parse_error);
}



// // Mocking the FileReader class
// class MockFileReader : public FileReader {
// public:
//     MOCK_CONST_METHOD1(isReadPathValid, void(const std::ifstream&));
//     MOCK_CONST_METHOD1(LoadFromFile, json(const std::string&));
// };

// // Test fixture for jsonReader
// class JsonReaderTest : public ::testing::Test {
// public:
//     void SetUp() override {
//         // Initialize mock FileReader
//         mock_file_reader = std::make_unique<MockFileReader>();
//         json_reader = std::make_unique<jsonReader>(std::vector<std::string>{"test_file.json"});
//         json_reader->setFileReader(std::move(mock_file_reader));
//     }

//     std::unique_ptr<MockFileReader> mock_file_reader;
//     std::unique_ptr<jsonReader> json_reader;
// };

// // Test case for successful data reading
// TEST_F(JsonReaderTest, ReadDataIntoGraphSuccess) {
//     // Prepare test data
//     json mock_json_data = R"(
//         {
//             "ID": 0,
//             "X": 80,
//             "Y": 270,
//             "floor": 0,
//             "distances": [5, 8, 1],
//             "connected": [1, 4, 3],
//             "classrooms": [
//                 { "name": "01", "description": "PIPR" },
//                 { "name": "02", "description": "PTCY" }
//             ]
//         }
//     )"_json;

//     // Set expectations
//     EXPECT_CALL(*mock_file_reader, isReadPathValid(testing::_));
//     EXPECT_CALL(*mock_file_reader, LoadFromFile("test_file.json")).WillOnce(testing::Return(mock_json_data));

//     // Perform the test
//     Graph graph = json_reader->ReadDataIntoGraph();

//     // Check if graph contains expected number of nodes
//     ASSERT_EQ(graph.getNodes().size(), 1);
//     // Additional assertions can be added to check the correctness of the nodes and their properties
// }

// // Test case for file not found
// TEST_F(JsonReaderTest, ReadDataIntoGraphFileNotFound) {
//     // Set expectations
//     EXPECT_CALL(*mock_file_reader, isReadPathValid(testing::_));
//     EXPECT_CALL(*mock_file_reader, LoadFromFile("test_file.json")).WillOnce(testing::Throw(std::runtime_error("File not found")));

//     // Perform the test and check if exception is thrown
//     ASSERT_THROW(json_reader->ReadDataIntoGraph(), std::runtime_error);
//     // Additional assertions can be added to check the behavior after the exception
// }

// // Test case for invalid JSON format
// TEST_F(JsonReaderTest, ReadDataIntoGraphInvalidJson) {
//     // Prepare test data with invalid JSON format
//     json mock_invalid_json_data = R"(
//         {
//             "ID": 0,
//             "X": 80,
//             "Y": 270,
//             "floor": 0,
//             "distances": [5, 8, 1],
//             "connected": [1, 4, 3],
//             "classrooms": [  // Missing closing brace for classrooms array
//                 { "name": "01", "description": "PIPR" },
//                 { "name": "02", "description": "PTCY" }
//             ]
//         }
//     )"_json;

//     // Set expectations
//     EXPECT_CALL(*mock_file_reader, isReadPathValid(testing::_));
//     EXPECT_CALL(*mock_file_reader, LoadFromFile("test_file.json")).WillOnce(testing::Return(mock_invalid_json_data));

//     // Perform the test and check if exception is thrown
//     ASSERT_THROW(json_reader->ReadDataIntoGraph(), nlohmann::detail::parse_error);
//     // Additional assertions can be added to check the behavior after the exception
// }



// class MockJsonReader : public jsonReader
// {
// public:
//     MockJsonReader() : jsonReader() {}
//     MockJsonReader(const std::vector<std::string>& pathsVec) : jsonReader(pathsVec) {}
//     // MOCK_METHOD(Graph, ReadDataIntoGraph, (), (const, override));
//     void mockLoadFromFile(const std::string& path) const
//     {
//         jsonReader::LoadFromFile(path);
//     }
//     MOCK_METHOD(nlohmann::json, LoadFromFile, (const std::string& path), (const));
// };

// TEST(JsonReaderTest, ReadValidJson) {
//     MockJsonReader mockReader({ "dummy_path" });
//     nlohmann::json jsonData = {
//         { "ID", 0 },
//         { "X", 80 },
//         { "Y", 270 },
//         { "floor", 0 },
//         { "distances", { 5, 8, 1 } },
//         { "connected", { 1, 4, 3 } },
//         { "classrooms", { 
//             { { "name", "01" }, { "description", "PIPR" } },
//             { { "name", "02" }, { "description", "PTCY" } }
//         } }
//     };

//     EXPECT_CALL(mockReader, LoadFromFile("dummy_path")).WillOnce(::testing::Return(jsonData));

//     Graph graph = mockReader.ReadDataIntoGraph();

//     // ASSERT_EQ(graph.getNodes().size(), 1);
//     Node node = graph.getNodes().at(0);

//     EXPECT_EQ(node.getID(), 0);
//     EXPECT_EQ(node.getX(), 80);
//     EXPECT_EQ(node.getY(), 270);
//     EXPECT_EQ(node.getFloor(), 0);
//     EXPECT_EQ(node.getDistances(), std::vector<int>({5, 8, 1}));
//     EXPECT_EQ(node.getNextNodes(), std::vector<int>({1, 4, 3}));
//     EXPECT_EQ(node.getClassrooms().size(), 2);
//     EXPECT_EQ(node.getClassrooms().at(0).getName(), "01");
//     EXPECT_EQ(node.getClassrooms().at(0).getDescription(), "PIPR");
//     EXPECT_EQ(node.getClassrooms().at(1).getName(), "02");
//     EXPECT_EQ(node.getClassrooms().at(1).getDescription(), "PTCY");
// }

// TEST(JsonReaderTest, ReadInvalidPath) {
//     MockJsonReader mockReader({ "invalid_path" });

//     EXPECT_CALL(mockReader, LoadFromFile("invalid_path")).WillOnce(::testing::Throw(std::runtime_error("Failed to open file")));

//     EXPECT_THROW({ mockReader.ReadDataIntoGraph();}, std::runtime_error);
// }

// TEST(JsonReaderTest, HandleInvalidJson) {
//     MockJsonReader mockReader({ "dummy_path" });

//     EXPECT_CALL(mockReader, LoadFromFile("dummy_path")).WillOnce(::testing::Return(nlohmann::json::parse("{ invalid json }", nullptr, false)));

//     EXPECT_THROW({mockReader.ReadDataIntoGraph();}, nlohmann::json::parse_error);
// }


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
