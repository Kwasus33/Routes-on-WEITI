#include "file_handler.hpp"
#include <sstream>
#include <string>
#include <iostream>


// Base class FileReader

FileReader::FileReader() : pathsVec(){};

FileReader::FileReader(const std::vector<std::string>& pathsVec): pathsVec(pathsVec) {};

FileReader::~FileReader() {};



//////      rapid json jsonReader    ///////

jsonReader::jsonReader() : FileReader(){};

jsonReader::jsonReader(const std::vector<std::string>& pathsVec) : FileReader(pathsVec){};

json jsonReader::LoadFromFile(const std::string path)
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

Graph jsonReader::ReadDataIntoGraph()
{
    Graph graph;

    for (const std::string path: pathsVec)
    {
        json json_file = LoadFromFile(path);

        for (const auto &obj : json_file)
        {
            Node node = createNode(obj);
            createClassrooms(obj, node);
            graph.addNode(node);
        }
    }

    return graph;
}

Node jsonReader::createNode(const json &obj)
{
    int id, X, Y, floor;
    std::vector<int> distancesVect, connectedNodes;

    if (obj.find("ID") != obj.end() && obj["ID"].is_number_integer())
        id = obj["ID"];

    if (obj.find("X") != obj.end() && obj["X"].is_number_integer())
        X = obj["X"];

    if (obj.find("Y") != obj.end() && obj["Y"].is_number_integer())
        Y = obj["Y"];

    if (obj.find("floor") != obj.end() && obj["floor"].is_number_integer())
        floor = obj["floor"];

    if (obj.find("distances") != obj.end() && obj["distances"].is_array())
        for (const auto &distance : obj["distances"])
        {
            if (distance.is_number_integer())
                distancesVect.push_back(distance);
        }

    if (obj.find("connected") != obj.end() && obj["connected"].is_array())
        for (const auto &connection : obj["connected"])
        {
            if (connection.is_number_integer())
                connectedNodes.push_back(connection);
        }

    return Node(id, distancesVect, connectedNodes, floor, X, Y);
}

void jsonReader::createClassrooms(const json& obj, Node& node)
{
    std::string name, description;

    if (obj.find("classrooms") != obj.end() && obj["classrooms"].is_array())
    {
        for (const auto &classroom : obj["classrooms"])
        {
            if (classroom.find("name") != classroom.end() && classroom["name"].is_string())
                name = classroom["name"];
            if (classroom.find("description") != classroom.end() && classroom["description"].is_string())
                description = classroom["description"];
            
            Classroom Class(name, description);
            node.addClassroom(Class);
        }
    }
}

void jsonReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}



/////   CSV reader - more prone to errors

//      csv konwencja zapisu:
//      id,x,y,floor,
//      distance,connected,distance,connected...
//      name,description,name,description...    -classrooms

csvReader::csvReader() : FileReader(){};

csvReader::csvReader(const std::vector<std::string>& pathsVec) : FileReader(pathsVec) {};

Graph csvReader::ReadDataIntoGraph()
{
    Graph graph;
    std::string line1;
    std::string line2;
    std::string line3;

    for(const std::string path: pathsVec)
    {
        std::ifstream fp_in(path);
        isReadPathValid(fp_in);

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
    }

    return graph;
};

Node csvReader::addNode(std::string& line1, std::string& line2, std::string& line3)
{
    Node node = createNode(line1, line2);
    createClassrooms(line3, node);
    return node;
};

Node csvReader::createNode(const std::string& line1, const std::string& line2)
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

        for (size_t i = 0; i < values.size(); i += 1)
        {
            distances.push_back(stoi(values.at(i)));
            connected.push_back(stoi(values.at(++i)));
        }

        return Node(id, distances, connected, floor, X, Y);
    }

    catch (const std::invalid_argument &error)
    {
        throw error;
    }

    catch (const std::out_of_range &error)   // for .at() method
    {
        throw error;
    }
}

void csvReader::createClassrooms(const std::string& line3, Node& node)
{
    std::vector<std::string> values;

    size_t start;
    size_t end;

    try
    {
        // reading third line
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

        for (size_t i = 0; i < values.size(); i += 1)
        {
            Classroom Class(values.at(i), values.at(++i));
            node.addClassroom(Class);
        }
    }

    catch (const std::invalid_argument &error)
    {
        throw error;
    }

    catch (const std::out_of_range &error)   // for .at() method
    {
        throw error;
    }
}

void csvReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open())
        std::cerr << "Failed to open file" << std::endl;
}
