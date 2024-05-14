#include "../include/file_handle.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include "json/json.h"


csvReader::csvReader(): path(), data() {};

csvReader::csvReader(const std::string &path): path(path) {};

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
    // std::vector<int> nextNodes;

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
            distances.push_back(stoi(values.at(i)));      
            ++i;
        }

        return Node(id, distances);
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





////// rapid json jsonReader

jsonReader::jsonReader(): path(), data() {};

jsonReader::jsonReader(const std::string &path): path(path) {};

std::vector<Node> jsonReader::getData() const {
    return data;
};

void jsonReader::LoadFromFile(const std::string path) {

    std::ifstream fp_in(path); //opens file
    isReadPathValid(fp_in);

    // Create a buffer and read the file into it
    char buffer[fp_in.size()];  // Adjust buffer size as needed
    FileReadStream stream(fp_in, buffer, sizeof(buffer));

    // Parse the JSON document
    Document document;
    document.ParseStream(stream);

    fp_in.close();

    if (document.HasParseError()) {
        std::cerr << "JSON parse error: " << GetParseError_En(document.GetParseError()) << std::endl;
        return 1;
    }

    addNodes();

    return 0;
}

Node jsonReader::addNodes(std::string& line) {
    std::vector<std::string> values;
    std::vector<int> distances;
    std::vector<int> nextNodes;

    // Access JSON data
    if (document.IsArray()) {

        for (SizeType i = 0; i < document.Size(); ++i) {

            const Value& item = document[i];
            
            if (item.IsObject()) {
                
                // Accessing "id" field
                if (item.HasMember("id") && item["id"].IsInt()) {
                    id = item["id"];
                }
                else {
                    std::cerr << "Failed to find or parse id field!" << std::endl;
                    return 1;
                }
                
                // Accessing "distances" array
                if (item.HasMember("distances") && item["distances"].IsArray()) {
                    const Value& distances = item["distances"];
                    std::cout << "Distances: ";
                    for (SizeType j = 0; j < distances.Size(); ++j) {
                        if (distances[j].IsInt()) {
                            std::cout << distances[j].GetInt() << " ";
                        }
                    }
                    std::cout << std::endl;
                } else {
                    std::cerr << "Failed to find or parse distances field!" << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "JSON array element is not an object!" << std::endl;
                return 1;
            }
        }
    } else {
        std::cerr << "JSON document is not an array!" << std::endl;
        return 1;
    }
    
    
    
    return Node(id, distances, nextNodes);
    

    catch (std::invalid_argument &error) {
        return;
    }
    catch (std::out_of_range &error) {  // for .at() method
        return;
    }
    // if error ocurrs the data line is skipped
};
