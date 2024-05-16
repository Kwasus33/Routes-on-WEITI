#include "file_handle.hpp"
#include <sstream>
#include <string>
#include <iostream>

//////      rapid json jsonReader    ///////

jsonReader::jsonReader() : path(){};

jsonReader::jsonReader(const std::string &path) : path(path){};

json jsonReader::LoadFromFile()
{

    std::ifstream fp_in(path); // opens file
    isReadPathValid(fp_in);

    // Read the JSON content into a json object
    json json_file;
    try
    {
        fp_in >> json_file;
    }
    catch (json::parse_error &e)
    {
        std::cerr << "Error parsing the JSON: " << e.what() << std::endl;
    }

    return json_file;
}

Graph jsonReader::addNodes()
{

    json json_file = LoadFromFile();

    Graph graph;

    // Iterate over each object in the array
    for (const auto &obj : json_file)
    {
        int id, X, Y, floor;
        std::vector<int> distancesVect, connectedNodes;
        std::string name, description;

        // Check if the object has an "id" field
        if (obj.find("ID") != obj.end() && obj["ID"].is_number_integer())
            id = obj["ID"];

        // Check if the object has an "X" field
        if (obj.find("X") != obj.end() && obj["X"].is_number_integer())
            X = obj["X"];

        // Check if the object has an "Y" field
        if (obj.find("Y") != obj.end() && obj["Y"].is_number_integer())
            Y = obj["Y"];

        // Check if the object has an "floor" field
        if (obj.find("floor") != obj.end() && obj["floor"].is_number_integer())
            floor = obj["floor"];

        // Check if the object has a "distances" field
        if (obj.find("distances") != obj.end() && obj["distances"].is_array())
            for (const auto &distance : obj["distances"])
                if (distance.is_number_integer())
                    distancesVect.push_back(distance);

        // Check if the object has a "connected" field
        if (obj.find("connected") != obj.end() && obj["connected"].is_array())
            for (const auto &connection : obj["connected"])
                if (connection.is_number_integer())
                    connectedNodes.push_back(connection);

        Node node(id, distancesVect, connectedNodes, floor, X, Y);

        // Check if the object has a "classrooms" field
        if (obj.find("classrooms") != obj.end() && obj["classrooms"].is_array())
            for (const auto &room : obj["classrooms"])
            {
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

void jsonReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}

/////   CSV reader - more prone to errors

// csv konwencja zapisu:
//      id,x,y,floor,
//      distance,connected,distance,connected...
//      name,description,name,description...    -classrooms

csvReader::csvReader() : path(){};

csvReader::csvReader(const std::string &path) : path(path){};

Graph csvReader::LoadFromFile(const std::string path)
{
    std::ifstream fp_in(path); // opens file
    isReadPathValid(fp_in);

    Graph graph;
    std::string line1;
    std::string line2;
    std::string line3;

    while (!fp_in.eof())
    {

        fp_in >> line1;
        if (!fp_in.eof())
            fp_in >> line2;
        if (!fp_in.eof())
            fp_in >> line3;

        if (!line1.empty() && !line2.empty() && !line3.empty())
        {
            Node new_node = addNode(line1, line2, line3);
            graph.addNode(new_node);
        }
    }
    fp_in.close();

    return graph;
};

Node csvReader::addNode(std::string &line1, std::string &line2, std::string &line3)
{

    std::vector<std::string> values;
    std::vector<int> distances, connected;

    size_t start;
    size_t end;

    try
    {
        // reading first line
        start = 0;
        end = line1.find(',');

        // while (end != std::string::npos) {
        while (line1[end] != '\n')
        {
            values.push_back(line1.substr(start, end - start));
            start = end + 1;
            end = line1.find(',', start);
        }
        values.push_back(line1.substr(start));

        int id = stoi(values.at(0));
        int X = stoi(values.at(1));
        int Y = stoi(values.at(2));
        int floor = stoi(values.at(3));

        // reading second line
        values.clear();
        start = 0;
        end = line2.find(',');

        // while (end != std::string::npos) {
        while (line2[end] != '\n')
        {
            values.push_back(line2.substr(start, end - start));
            start = end + 1;
            end = line2.find(',', start);
        }
        values.push_back(line2.substr(start));

        for (size_t i = 0; i < values.size(); i += 2)
        {
            distances.push_back(stoi(values.at(i)));
            connected.push_back(stoi(values.at(++i)));
        }

        // creating node
        Node node(id, distances, connected, floor, X, Y);

        // reading third line
        values.clear();
        start = 0;
        end = line3.find(',');

        // while (end != std::string::npos) {
        while (line3[end] != '\n')
        {
            values.push_back(line3.substr(start, end - start));
            start = end + 1;
            end = line3.find(',', start);
        }
        values.push_back(line3.substr(start));

        for (size_t i = 0; i < values.size(); i += 2)
        {
            Classroom room(values.at(i), values.at(++i));
            node.addClassroom(room);
        }

        return node;
    }
    catch (const std::invalid_argument &error)
    {
        throw error;
    }
    catch (const std::out_of_range &error)
    { // for .at() method
        throw error;
    }
};

void csvReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}
