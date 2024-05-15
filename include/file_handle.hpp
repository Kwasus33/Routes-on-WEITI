#pragma once
// #include "node.hpp"
#include "graph.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


class csvReader {
    public:
        csvReader();
        csvReader(const std::string& path);
        void LoadFromFile(const std::string path);
        std::vector<Node> getData() const;
    private:
        std::string path;
        std::vector<Node> data;
        void addNode(std::string& line);
        void isReadPathValid(const std::ifstream& fp) const; // dodane jako metody public nie private bo operatory z nich będą korzystać
};

class jsonReader {
    public:
        jsonReader();
        jsonReader(const std::string& path);
        json LoadFromFile();
        Graph addNodes(json json_file);
    private:
        std::string path;
        void isReadPathValid(const std::ifstream& fp) const; // dodane jako metody public nie private bo operatory z nich będą korzystać
};