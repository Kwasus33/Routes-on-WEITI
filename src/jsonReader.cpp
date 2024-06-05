#include "jsonReader.hpp"

JSONReader::JSONReader() : FileReader(){};

JSONReader::JSONReader(const std::vector<std::string> &pathsVec) : FileReader(pathsVec){};

Graph JSONReader::readDataIntoGraph() const
{
    Graph graph;

    for (const std::string &path : pathsVec)
    {
        json json_file = loadFromFile(path);

        for (const auto &obj : json_file)
        {
            Node node = createNode(obj);
            createClassrooms(obj, node);
            graph.addNode(node);
        }
    }

    return graph;
}

json JSONReader::loadFromFile(const std::string &path) const
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

Node JSONReader::createNode(const json &obj) const
{
    int id, X, Y, floor;
    std::vector<int> distancesVect, connectedNodes;
    bool flag = true;

    if (obj.find("ID") != obj.end() && obj["ID"].is_number_integer())
    {
        id = obj["ID"];
    }
    else
    {
        flag = false;
    }

    if (obj.find("X") != obj.end() && obj["X"].is_number_integer())
    {
        X = obj["X"];
    }
    else
    {
        flag = false;
    }

    if (obj.find("Y") != obj.end() && obj["Y"].is_number_integer())
    {
        Y = obj["Y"];
    }
    else
    {
        flag = false;
    }

    if (obj.find("floor") != obj.end() && obj["floor"].is_number_integer())
    {
        floor = obj["floor"];
    }
    else
    {
        flag = false;
    }

    if (obj.find("distances") != obj.end() && obj["distances"].is_array())
    {
        for (const auto &distance : obj["distances"])
        {
            if (distance.is_number_integer())
            {
                distancesVect.push_back(distance);
            }
        }
    }
    else
    {
        flag = false;
    }

    if (obj.find("connected") != obj.end() && obj["connected"].is_array())
    {
        for (const auto &connection : obj["connected"])
        {
            if (connection.is_number_integer())
            {
                connectedNodes.push_back(connection);
            }
        }
    }
    else
    {
        flag = false;
    }

    if (!flag)
    {
        throw std::invalid_argument("Invalid dict object in JSON file.");
    }

    return Node(id, distancesVect, connectedNodes, floor, X, Y);
}

void JSONReader::createClassrooms(const json &obj, Node &node) const
{
    std::string name, description;
    bool flag = true;

    if (obj.find("classrooms") != obj.end() && obj["classrooms"].is_array())
    {
        for (const auto &classroom : obj["classrooms"])
        {
            if (classroom.find("name") != classroom.end() && classroom["name"].is_string())
            {
                name = classroom["name"];
            }
            else
            {
                flag = false;
            }
            if (classroom.find("description") != classroom.end() && classroom["description"].is_string())
            {
                description = classroom["description"];
            }
            else
            {
                flag = false;
            }
            if (flag)
            {
                Classroom Class(name, description);
                node.addClassroom(Class);
            }
            else
            {
                flag = true;
            }
        }
    }
    else
    {
        throw std::invalid_argument("Invalid dict object in JSON file.");
    }
}

void JSONReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
    }
}
