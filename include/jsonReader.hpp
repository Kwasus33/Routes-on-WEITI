#pragma once
#include "file_handler.hpp"
#include "nlohmann/json.hpp"


using json = nlohmann::json;

class JSONReader: public FileReader {
    public:
        JSONReader();
        JSONReader(const std::vector<std::string>& pathsVec);
        Graph readDataIntoGraph() const;
    // private:
    protected:
        json loadFromFile(const std::string& path) const;
        void isReadPathValid(const std::ifstream& fp) const;
        Node createNode(const json& obj) const;
        void createClassrooms(const json& obj, Node& node) const;
};