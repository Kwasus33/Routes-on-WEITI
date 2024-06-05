#pragma once
#include "graph.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class FileReader {
    public:
        FileReader();
        FileReader(const std::vector<std::string>& pathsVec);
        virtual ~FileReader();
        virtual Graph ReadDataIntoGraph() const = 0;
    protected:
        std::vector<std::string> pathsVec;
};
