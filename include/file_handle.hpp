#pragma once
#include "node.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <fstream>
// #include "../include/file_handle.hpp"
// #include "../build/_deps/jsonrapid-src/include/rapidjson/document.h"
// #include <../build/_deps/boost-src/libs/json>
#include "json.hpp"


class csvReader {
    public:
        csvReader();
        csvReader(const std::string& path);
        void LoadFromFile(const std::string path);
        std::vector<Node> getData() const;
        //friend std::istream& operator >>(std::istream &is, const csvReader &csv);
    private:
        std::string path;
        std::vector<Node> data;
        void addNode(std::string& line);
        void isReadPathValid(const std::ifstream& fp) const; // dodane jako metody public nie private bo operatory z nich będą korzystać
        //void isWritePathValid(const std::ofstream& fp) const;
};

class jsonReader {
    public:
        jsonReader();
        jsonReader(const std::string& path);
        void LoadFromFile(const std::string path);
        std::vector<Node> getData() const;
        //sfriend std::istream& operator >>(std::istream &is, const jsonReader &json);
    private:
        std::string path;
        std::vector<Node> data;
        std::vector<Node> addNodes(json json_file);
        void isReadPathValid(const std::ifstream& fp) const; // dodane jako metody public nie private bo operatory z nich będą korzystać
};