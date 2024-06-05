#include <gtest/gtest.h>
#include "jsonReader.hpp"
#include "csvReader.hpp"
#include <stdexcept>
#include <string>
#include <cstdio>

class TemporaryFile 
{
    public:
        TemporaryFile(const std::string& content) 
        {
            char tmpFilename[FILENAME_MAX];

    #if defined(_WIN32) || defined(_WIN64)
            if (tmpnam_s(tmpFilename) != 0)
            {
                throw std::runtime_error("Failed to create temporary file");
            }
    #elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
            std::strcpy(tmpFilename, "/tmp/tmpfile.XXXXXX");
            int fd = mkstemp(tmpFilename);

            if (fd == -1)
            {
                throw std::runtime_error("Failed to create temporary file");
            }
    #else
            #error "TemporaryFile is not implemented for this platform"
    #endif

            filename = tmpFilename;
            std::ofstream tmpFile(filename);

            if (!tmpFile.is_open()) 
            {
    #if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
                close(fd);
    #endif
                throw std::runtime_error("Failed to open temporary file");
            }

            tmpFile << content;
            tmpFile.close();

    #if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
            close(fd);
    #endif
        }

        ~TemporaryFile()
        {
            std::remove(filename.c_str());
        }

        const std::string& getFilename() const
        {
            return filename;
        }

        TemporaryFile(const TemporaryFile&) = delete;
        TemporaryFile& operator=(const TemporaryFile&) = delete;

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


class FileReaderTest : public ::testing::Test {
protected:
    std::unique_ptr<FileReader> ptrJson;
    std::unique_ptr<FileReader> ptrCsv;

    void SetUp() override
    {
        std::vector<std::string> pathsVecJson;
        std::vector<std::string> pathsVecCsv;
        ptrJson = std::make_unique<JSONReader>(pathsVecJson);
        ptrCsv = std::make_unique<JSONReader>(pathsVecCsv);
    }
};


// ########### Tests for JSONReader ###########

TEST(JSONReaderTest, readDataIntoGraphSuccess)
{
    TemporaryFile tempFile(mock_json_content);

    JSONReader json_reader({tempFile.getFilename()});
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
}

TEST(JSONReaderTest, readDataIntoGraphFileNotFound)
{
    JSONReader json_reader({"nonexistent_file.json"});
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "Failed to open file\n");
}

TEST(JSONReaderTest, readDataIntoGraphInvalidJson) {

    std::string invalid_json_content = "invalid json";
    TemporaryFile tempFile(invalid_json_content);

    JSONReader json_reader({tempFile.getFilename()});

    ASSERT_ANY_THROW(json_reader.readDataIntoGraph());
}

// ########### Tests for CSVReader ###########
