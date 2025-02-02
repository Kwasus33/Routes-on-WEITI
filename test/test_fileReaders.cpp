#include <gtest/gtest.h>
#include "jsonReader.hpp"
#include "csvReader.hpp"
#include <stdexcept>
#include <string>
#include <cstdio>


void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
    }
    outFile << content;
    outFile.close();
}

const static std::string mock_json_content =
R"(
    [
        {
            "ID": 0,
            "X": 80,
            "Y": 270,
            "floor": 0,
            "distances": [5, 8, 1],
            "connected": [1, 4, 3],
            "classrooms": [
                {"name": "01", "description": "PIPR"},
                {"name": "02", "description": "PTCY"}
            ]
        }
    ]
)";

const static std::string CsvContent =
    "1,100,200,0\n,\nClassroom1,Description1,Classroom2,Description2";


// ########### Tests for JSONReader ###########

TEST(JSONReaderTest, readDataIntoGraphSuccess)
{
    std::string testFilename = "test_file.json";
    createTestFile(testFilename, mock_json_content);

    JSONReader json_reader({testFilename});
    Graph graph = json_reader.readDataIntoGraph();

    ASSERT_EQ(graph.getNodes().size(), 1);

    Node node = graph.getNodes().at(0);
    ASSERT_EQ(node.getID(), 0);
    ASSERT_EQ(node.getX(), 80);
    ASSERT_EQ(node.getY(), 270);
    ASSERT_EQ(node.getFloor(), 0);
  
    auto classrooms = node.getClassrooms();
    ASSERT_EQ(classrooms.size(), 2);
    ASSERT_EQ(classrooms[0].getName(), "01");
    ASSERT_EQ(classrooms[0].getDescription(), "PIPR");
    ASSERT_EQ(classrooms[1].getName(), "02");
    ASSERT_EQ(classrooms[1].getDescription(), "PTCY");

    std::remove(testFilename.c_str());
}

TEST(JSONReaderTest, readNonExistingJsonFile)
{
    std::stringstream buffer;
    std::streambuf* prevbuf = std::cerr.rdbuf(buffer.rdbuf());

    JSONReader reader({"non_existing_file.json"});
    reader.readDataIntoGraph();

    std::cerr.rdbuf(prevbuf);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("Failed to open file\n"), std::string::npos);
}


// ########### Tests for CSVReader ###########

TEST(CSVReaderTest, ReadValidCSVFile) {
    std::string testFilename = "test_file.csv";

    createTestFile(testFilename, CsvContent);

    CSVReader reader({testFilename});
    Graph graph = reader.readDataIntoGraph();

    ASSERT_EQ(graph.getNodes().size(), 1);

    Node node = graph.getNodes().at(0);
    EXPECT_EQ(node.getID(), 1);
    EXPECT_EQ(node.getX(), 100);
    EXPECT_EQ(node.getY(), 200);
    EXPECT_EQ(node.getFloor(), 0);

    EXPECT_EQ(node.getClassrooms().size(), 2);
    EXPECT_EQ(node.getClassrooms()[0].getName(), "Classroom1");
    EXPECT_EQ(node.getClassrooms()[0].getDescription(), "Description1");
    EXPECT_EQ(node.getClassrooms()[1].getName(), "Classroom2");
    EXPECT_EQ(node.getClassrooms()[1].getDescription(), "Description2");

    std::remove(testFilename.c_str());
}

TEST(CSVReaderTest, ReadNonExistingCSVFile) {
    std::stringstream buffer;
    std::streambuf* prevbuf = std::cerr.rdbuf(buffer.rdbuf());

    CSVReader reader({"non_existing_file_2.csv"});
    EXPECT_THROW(reader.readDataIntoGraph(), std::invalid_argument);

    std::cerr.rdbuf(prevbuf);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("Failed to open file\n"), std::string::npos);
}