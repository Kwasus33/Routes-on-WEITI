#pragma once
#include "file_handler.hpp"
#include "nlohmann/json.hpp"


using json = nlohmann::json;

class jsonReader: public FileReader {
    public:
        jsonReader();
        jsonReader(const std::vector<std::string>& pathsVec);
        Graph ReadDataIntoGraph();
    private:
        json LoadFromFile(const std::string& path);
        void isReadPathValid(const std::ifstream& fp) const;
        Node createNode(const json& obj);
        void createClassrooms(const json& obj, Node& node);
};