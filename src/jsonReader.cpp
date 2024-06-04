#include "jsonReader.hpp"


jsonReader::jsonReader() : FileReader(){};

jsonReader::jsonReader(const std::vector<std::string>& pathsVec) : FileReader(pathsVec){};

Graph jsonReader::ReadDataIntoGraph()
{
    Graph graph;

    for (const std::string& path: pathsVec)
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

json jsonReader::LoadFromFile(const std::string& path)
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

Node jsonReader::createNode(const json &obj)
{
    int id, X, Y, floor;
    std::vector<int> distancesVect, connectedNodes;

    if (obj.find("ID") != obj.end() && obj["ID"].is_number_integer()){
        id = obj["ID"];
    }

    if (obj.find("X") != obj.end() && obj["X"].is_number_integer()){
        X = obj["X"];
    }

    if (obj.find("Y") != obj.end() && obj["Y"].is_number_integer()){
        Y = obj["Y"];
    }

    if (obj.find("floor") != obj.end() && obj["floor"].is_number_integer()){
        floor = obj["floor"];
    }

    if (obj.find("distances") != obj.end() && obj["distances"].is_array())
    {
        for (const auto &distance : obj["distances"])
        {
            if (distance.is_number_integer()){
                distancesVect.push_back(distance);
            }
        }
    }

    if (obj.find("connected") != obj.end() && obj["connected"].is_array())
    {
        for (const auto &connection : obj["connected"])
        {
            if (connection.is_number_integer()){
                connectedNodes.push_back(connection);
            }
        }
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
            if (classroom.find("name") != classroom.end() && classroom["name"].is_string()){
                name = classroom["name"];
            }
            if (classroom.find("description") != classroom.end() && classroom["description"].is_string()){
                description = classroom["description"];
            }
            
            Classroom Class(name, description);
            node.addClassroom(Class);
        }
    }
}

void jsonReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open()){
        std::cerr << "Failed to open file" << std::endl;
    }
}
