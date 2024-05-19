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
        FileReader(const std::string& path);
        virtual Graph ReadDataIntoGraph() = 0;
    private:
        std::string path;
    protected:
        virtual void isReadPathValid(const std::ifstream& fp) const;

};

class jsonReader: public FileReader {
    public:
        jsonReader();
        jsonReader(const std::string& path);
        Graph ReadDataIntoGraph();
    private:
        std::string path;
        json LoadFromFile();
    protected:
        void isReadPathValid(const std::ifstream& fp) const;
};

class csvReader: public FileReader {
    public:
        csvReader();
        csvReader(const std::string& path);
        Graph ReadDataIntoGraph();
    private:
        std::string path;
        Node addNode(std::string& line1, std::string& line2, std::string& line3);
    protected:
        void isReadPathValid(const std::ifstream& fp) const;
};