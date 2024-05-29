#pragma once
#include "graph.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


class FileReader {
    public:
        FileReader();
        FileReader(const std::vector<std::string>& pathsVec);
        virtual ~FileReader();
        virtual Graph ReadDataIntoGraph() = 0;
    protected:
        std::vector<std::string> pathsVec;
};

class jsonReader: public FileReader {
    public:
        jsonReader();
        jsonReader(const std::vector<std::string>& pathsVec);
        Graph ReadDataIntoGraph();
    private:
        json LoadFromFile(const std::string path);
        void isReadPathValid(const std::ifstream& fp) const;
        Node createNode(const json& obj);
        void createClassrooms(const json& obj, Node& node);
};

class csvReader: public FileReader {
    public:
        csvReader();
        csvReader(const std::vector<std::string>& pathsVec);
        Graph ReadDataIntoGraph();
    private:
        Node addNode(std::string& line1, std::string& line2, std::string& line3);
        void isReadPathValid(const std::ifstream& fp) const;
        Node createNode(const std::string& line1, const std::string& line2);
        void createClassrooms(const std::string& line3, Node& node); 
};