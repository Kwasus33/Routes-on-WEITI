#pragma once
// #include "node.hpp"
#include "graph.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


class jsonReader {
    public:
        jsonReader();
        jsonReader(const std::string& path);
        Graph addNodes();
    private:
        std::string path;
        json LoadFromFile();
        void isReadPathValid(const std::ifstream& fp) const; // dodane jako metody public nie private bo operatory z nich będą korzystać
};

class csvReader {
    public:
        csvReader();
        csvReader(const std::string& path);
        Graph LoadFromFile(const std::string path);
    private:
        std::string path;
        Node csvReader::addNode(std::string& line1, std::string& line2, std::string& line3);
        void isReadPathValid(const std::ifstream& fp) const; // dodane jako metody public nie private bo operatory z nich będą korzystać
};