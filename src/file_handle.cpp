#include "file_handle.hpp"
#include <sstream>
#include <string>
#include <iostream>


csvReader::csvReader(): path(), data() {};

csvReader::csvReader(const std::string &path, const std::vector<Node> &data): path(path), data(data) {};

void csvReader::readData() {

};

std::vector<Node> csvReader::getData() const {
    return data;
};

void csvReader::LoadFromFile(const std::string path) {
    std::ifstream fp_in(path); //opens file
    isReadPathValid(fp_in);
    std::string line;
    while(!fp_in.eof()) {
        fp_in >> line;
        if(!line.empty())
            addNode(line);
    }
    fp_in.close();
}

Node csvReader::addNode(std::string& line) {
    std::vector<std::string> values;
    std::vector<int> distances;
    std::vector<int> nextNodes;

    size_t start = 0;
    size_t end = line.find(',');

    // w csv zapis w konwencji id,next_node,distance,next_node,distance,...

    try {
        // while (end != std::string::npos) {
        while (end != '\n') {
            values.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(',', start);
        }
        values.push_back(line.substr(start));

        int id = stoi(values.at(0));
        
        int i = 1;
        while (i < size(values)) {
            nextNodes.push_back(stoi(values.at(i)));  
            distances.push_back(stoi(values.at(++i)));      
            i += 2;
        }

        return Node(id, distances, nextNodes);
    }
    catch (std::invalid_argument &error) {
        return;
    }
    catch (std::out_of_range &error) {  // for .at() method
        return;
    }
    // if error ocurrs the data line is skipped
};

void csvReader::isReadPathValid(const std::ifstream &fp) const{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}

// not finisehed - maybe added
// std::istream& operator >>(std::istream &is, csvReader& csvReader) {
// std::istream& csvReader::operator >>(std::istream &is, const csvReader &csv) {
//     std::string line;

//     while(is) {
//         is >> line;
//         csvReader.addNode(line);
//     }

//     return is;
// }
