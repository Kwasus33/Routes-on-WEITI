#pragma once
#include "file_handler.hpp"


class csvReader: public FileReader {
    public:
        csvReader();
        csvReader(const std::vector<std::string>& pathsVec);
        Graph ReadDataIntoGraph() const;
    private:
        Node addNode(std::string& line1, std::string& line2, std::string& line3) const;
        void isReadPathValid(const std::ifstream& fp) const;
        Node createNode(const std::string& line1, const std::string& line2) const;
        void createClassrooms(const std::string& line3, Node& node) const;
};