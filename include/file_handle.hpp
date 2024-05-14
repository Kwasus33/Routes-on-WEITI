#pragma once
#include "node.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <fstream>


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
        Node addNode(std::string& line);
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
        Node addNodes(std::string& line);
        void isReadPathValid(const std::ifstream& fp) const; // dodane jako metody public nie private bo operatory z nich będą korzystać
};