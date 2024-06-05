#pragma once
#include "file_handler.hpp"
#include "nlohmann/json.hpp"


using json = nlohmann::json;

class jsonReader: public FileReader {
    public:
        jsonReader();
        jsonReader(const std::vector<std::string>& pathsVec);
        Graph ReadDataIntoGraph() const;
    // private:
    protected:
        json LoadFromFile(const std::string& path) const;
        void isReadPathValid(const std::ifstream& fp) const;
        Node createNode(const json& obj) const;
        void createClassrooms(const json& obj, Node& node) const;
};