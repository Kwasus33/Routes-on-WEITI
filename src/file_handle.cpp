#include "file_handle.hpp"
#include <sstream>
#include <string>
#include <iostream>


// csvReader::csvReader(): path(), data() {};

// csvReader::csvReader(const std::string &path): path(path) {};

// std::vector<Node> csvReader::getData() const {
//     return data;
// };

// void csvReader::LoadFromFile(const std::string path) {
//     std::ifstream fp_in(path); //opens file
//     isReadPathValid(fp_in);
//     std::string line;
//     while(!fp_in.eof()) {
//         fp_in >> line;
//         if(!line.empty())
//             addNode(line);
//     }
//     fp_in.close();
// };

// void csvReader::addNode(std::string& line) {
//     std::vector<std::string> values;
//     std::vector<int> distances;

//     size_t start = 0;
//     size_t end = line.find(',');

//     try {
//         // while (end != std::string::npos) {
//         while (line[end] != '\n') {
//             values.push_back(line.substr(start, end - start));
//             start = end + 1;
//             end = line.find(',', start);
//         }
//         values.push_back(line.substr(start));

//         int id = stoi(values.at(0));
        
//         for(size_t i = 1; i < values.size(); ++i) {
//             distances.push_back(stoi(values.at(i)));      
//         }

//         data.push_back(Node(id, distances));
//     }
//     catch (const std::invalid_argument& error) {
//         return;
//     }
//     catch (const std::out_of_range& error) {  // for .at() method
//         return;
//     }
// };

// void csvReader::isReadPathValid(const std::ifstream &fp) const{
//     if (!fp.is_open())
//         std::cerr << "Failed to open file" << std::endl;
// }

//////      rapid json jsonReader    ///////

jsonReader::jsonReader(): path() {};

jsonReader::jsonReader(const std::string &path): path(path) {};

json jsonReader::LoadFromFile() {

    std::ifstream fp_in(path); //opens file
    isReadPathValid(fp_in);

    // Read the JSON content into a json object
    json json_file;
    try {
        fp_in >> json_file;
    }
    catch (json::parse_error& e) {
        std::cerr << "Error parsing the JSON: " << e.what() << std::endl;
    }

    return json_file;
}

Graph jsonReader::addNodes(json json_file) {
    
    Graph graph;

    // Iterate over each object in the array
    for (const auto& obj : json_file) {
        int id;
        std::vector<int> distancesVect;
        std::vector<int> connectedNodes;
        std::string name;
        std::string description;

        // Check if the object has an "id" field
        if (obj.find("ID") != obj.end() && obj["ID"].is_number_integer())
            id = obj["ID"];

        // Check if the object has a "distances" field
        if (obj.find("distances") != obj.end() && obj["distances"].is_array())
            for (const auto& distance : obj["distances"])
                if (distance.is_number_integer())
                    distancesVect.push_back(distance);

        // Check if the object has a "connected" field
        if (obj.find("connected") != obj.end() && obj["connected"].is_array())
            for (const auto& connection : obj["connected"])
                if (connection.is_number_integer())
                    connectedNodes.push_back(connection);

        Node node(id, distancesVect, connectedNodes);

        // Check if the object has a "classrooms" field
        if (obj.find("classrooms") != obj.end() && obj["classrooms"].is_array())
            for (const auto& room : obj["classrooms"]) {
                if (room.find("name") != room.end() && room["name"].is_string())
                    name = room["name"];
                if (room.find("description") != room.end() && room["description"].is_string())
                    description = room["description"];
                
                Classroom Classroom(name, description);
                node.addClassroom(Classroom);
            }

        graph.addNode(node);
    }
    return graph;
}

void jsonReader::isReadPathValid(const std::ifstream &fp) const{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}
