#include "file_handle.hpp"
#include <sstream>
#include <string>
#include <iostream>
// #include "json.hpp"

using json = nlohmann::json;

// using namespace rapidjson;
// using namespace boost::json;


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
};

void csvReader::addNode(std::string& line) {
    std::vector<std::string> values;
    std::vector<int> distances;

    size_t start = 0;
    size_t end = line.find(',');

    try {
        // while (end != std::string::npos) {
        while (line[end] != '\n') {
            values.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(',', start);
        }
        values.push_back(line.substr(start));

        int id = stoi(values.at(0));
        
        for(size_t i = 1; i < values.size(); ++i) {
            distances.push_back(stoi(values.at(i)));      
        }

        data.push_back(Node(id, distances));
    }
    catch (const std::invalid_argument& error) {
        return;
    }
    catch (const std::out_of_range& error) {  // for .at() method
        return;
    }
};

void csvReader::isReadPathValid(const std::ifstream &fp) const{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}

//////      rapid json jsonReader    ///////

jsonReader::jsonReader(): path(), data() {};

jsonReader::jsonReader(const std::string &path): path(path) {};

std::vector<Node> jsonReader::getData() const {
    return data;
};

void jsonReader::LoadFromFile(const std::string path) {

    std::ifstream fp_in(path); //opens file
    isReadPathValid(fp_in);

    // Read the JSON content into a json object
    json json_file;
    try {
        json >> json_file;
    }
    catch (json::parse_error& e) {
        std::cerr << "Error parsing the JSON: " << e.what() << std::endl;
        return;
    }

    addNodes(json_file);

    return;
}

std::vector<Node> jsonReader::addNodes(json json_file) {
    
    // std::vector<Node> Nodes;
    // int id;

    // // Iterate over each object in the array
    // for (const auto& obj : jv.as_array()) {
    //     std::vector<int> distancesVect;

    //     // Check if the object has an "id" field
    //     if (auto id = obj.at("id"); id.is_int64())
    //         id = id.as_int64();

    //     // Check if the object has a "distances" field
    //     if (auto distances = obj.at("distances"); distances.is_array())
    //         for (const auto& distance : distances.as_array())
    //             if (distance.is_int64())
    //                 distancesVect.push_back(distance.as_int64());

    //     Nodes.push_back(Node(id, distancesVect));
    // }
    
    // return Nodes;

    std::vector<Node> Nodes;
    int id;

// Iterate over each object in the array
    for (const auto& obj : json_file) {
        std::vector<int> distancesVect;

        // Check if the object has an "id" field
        if (obj.find("id") != obj.end() && obj["id"].is_number_integer())
            id = obj["id"];

        // Check if the object has a "distances" field
        if (obj.find("distances") != obj.end() && obj["distances"].is_array())
            for (const auto& distance : obj["distances"])
                if (distance.is_number_integer())
                    distancesVect.push_back(distance);

        Nodes.push_back(Node(id, distancesVect));
    }
}

// void jsonReader::LoadFromFile(const std::string path) {

//     std::ifstream fp_in(path); //opens file
//     isReadPathValid(fp_in);

//     // Read the JSON content into a string
//     std::string jsonContent((std::istreambuf_iterator<char>(fp_in)), (std::istreambuf_iterator<char>()));

//     // Close the file stream
//     fp_in.close();

//     // Parse the JSON content
//     error_code ec;

//     auto jv = parse(jsonContent, ec);
    
//     if (ec) {
//         std::cerr << "Error parsing the JSON: " << ec.message() << std::endl;
//         return;
//     }

//     // Check if the parsed value is an array
//     if (!jv.is_array()) {
//         std::cerr << "JSON content is not an array." << std::endl;
//         return;
//     }

//     addNodes(jv);
//     return;

    // std::ifstream fp_in(path); //opens file
    // isReadPathValid(fp_in);

    // // Read the JSON content into a string
    // std::string jsonContent((std::istreambuf_iterator<char>(fp_in)), (std::istreambuf_iterator<char>()));

    // // Close the file stream
    // fp_in.close();

    // // Parse the JSON content
    // Document document;

    // if (document.Parse(jsonContent.c_str()).HasParseError()) {
    //     std::cerr << "Error parsing the JSON." << std::endl;
    //     return;
    // }

    // // Access JSON array elements
    // if (!document.IsArray()) {
    //     std::cerr << "JSON content is not an array." << std::endl;
    //     return;
    // }

    // addNodes(document);
    // return;

// }
// nie czyta pliku document.h z biblioteki rapidjson

// std::vector<Node> jsonReader::addNodes(auto jv) {
    
//     std::vector<Node> Nodes;
//     int id;

//     // Iterate over each object in the array
//     for (const auto& obj : jv.as_array()) {
//         std::vector<int> distancesVect;

//         // Check if the object has an "id" field
//         if (auto id = obj.at("id"); id.is_int64())
//             id = id.as_int64();

//         // Check if the object has a "distances" field
//         if (auto distances = obj.at("distances"); distances.is_array())
//             for (const auto& distance : distances.as_array())
//                 if (distance.is_int64())
//                     distancesVect.push_back(distance.as_int64());

//         Nodes.push_back(Node(id, distancesVect));
//     }
    
//     return Nodes;
    
    // // Iterate over each object in the array
    // for (SizeType i = 0; i < document.Size(); i++) {
    //     const Value& obj = document[i];

    //     // Check if the object has an "id" field
    //     if (obj.HasMember("id") && obj["id"].IsInt()) {
    //         id = obj["id"].GetInt();
    //     }

    //     // Check if the object has a "distances" field
    //     if (obj.HasMember("distances") && obj["distances"].IsArray()) {
    //         const Value& distances = obj["distances"];
    //         for (SizeType j = 0; j < distances.Size(); j++)
    //             if (distances[j].IsInt())
    //                 distancesVect.push_back(distances[j].GetInt());
    //     }

    //     Nodes.push_back(Node(id, distancesVect));        
    // }
    // return Nodes;
// }

void jsonReader::isReadPathValid(const std::ifstream &fp) const{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}
