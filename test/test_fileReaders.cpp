#include <gtest/gtest.h>
#include "jsonReader.hpp"
#include "csvReader.hpp"
#include <cstdio>
#include <string>
#include <memory>


class TemporaryFile {
public:
    TemporaryFile(const std::string& content) {
        char tmpFilename[] = "/tmp/tmpfile.XXXXXX";
        int fd = mkstemp(tmpFilename);

        if (fd == -1) {
            throw std::runtime_error("Failed to create temporary file");
        }

        filename = tmpFilename;
        std::ofstream tmpFile(filename);
        tmpFile << content;
        tmpFile.close();

        close(fd);
    }

    ~TemporaryFile() {
        std::remove(filename.c_str());
    }

    const std::string& getFilename() const {
        return filename;
    }

private:
    std::string filename;
};

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


// Class to swap between jsonReader and csvReader during tests
class FileReaderTest : public ::testing::Test {
protected:
    std::unique_ptr<FileReader> ptrJson;
    std::unique_ptr<FileReader> ptrCsv;

    void SetUp() override {
        // Initialize jsonReader with empty pathsVec
        std::vector<std::string> pathsVecJson;
        std::vector<std::string> pathsVecCsv;
        ptrJson = std::make_unique<jsonReader>(pathsVecJson);
        ptrCsv = std::make_unique<jsonReader>(pathsVecCsv);
    }
};


// ########### Tests for jsonReader ###########

// TEST_F(JsonReaderTest, ReadDataIntoGraphSuccess) {
TEST(JsonReaderTest, ReadDataIntoGraphSuccess) {

    TemporaryFile tempFile(mock_json_content);

    // json_reader->pathsVec.push_back(tempFile.getFilename());
    jsonReader json_reader({tempFile.getFilename()});

    // Graph graph = json_reader->ReadDataIntoGraph();
    Graph graph = json_reader.ReadDataIntoGraph();

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
}

// TEST_F(JsonReaderTest, ReadDataIntoGraphFileNotFound)
TEST(JsonReaderTest, ReadDataIntoGraphFileNotFound) {

    // json_reader->pathsVec.push_back("nonexistent_file.json");
    jsonReader json_reader({"nonexistent_file.json"});
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "Failed to open file\n");
}

// TEST_F(JsonReaderTest, ReadDataIntoGraphInvalidJson)
TEST(JsonReaderTest, ReadDataIntoGraphInvalidJson) {

    std::string invalid_json_content = "invalid json";
    TemporaryFile tempFile(invalid_json_content);

    // json_reader->pathsVec.push_back(tempFile.getFilename());
    jsonReader json_reader({tempFile.getFilename()});

    // ASSERT_ANY_THROW(json_reader->ReadDataIntoGraph());
    ASSERT_ANY_THROW(json_reader.ReadDataIntoGraph());
}

// ########### Tests for csvReader ###########
