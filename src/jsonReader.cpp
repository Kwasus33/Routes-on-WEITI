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
    std::ifstream fp_in(path);
    isReadPathValid(fp_in);

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

template <typename T, typename Func>
T JSONReader::getJsonValue(const json& obj, const std::string& key, Func func) const
{
    if (obj.find(key) != obj.end() && func(obj[key]))
    {
        return obj[key];
    }
    else
    {
        throw std::invalid_argument(key + " not found or not an integer in JSON file.");
    }
}

template <typename T, typename Func>
std::vector<T> JSONReader::getJsonVec(const json& obj, const std::string& key, Func func) const 
{
    std::vector<T> vec;
    if (obj.find(key) != obj.end() && obj[key].is_array())
    {
        for (const auto &item : obj[key])
        {
            if (func(item))
            {
                vec.push_back(item);
            }
        }
    }
    else
    {
        throw std::invalid_argument(key + " not found or not an array in JSON file.");
    }

    return vec;
}

Node JSONReader::createNode(const json &obj) const
{
    int id = getJsonValue<int>(obj, "ID", [](const nlohmann::json& j){ return j.is_number_integer(); });
    int X = getJsonValue<int>(obj, "X", [](const nlohmann::json& j){ return j.is_number_integer(); });
    int Y = getJsonValue<int>(obj, "Y", [](const nlohmann::json& j){ return j.is_number_integer(); });
    int floor = getJsonValue<int>(obj, "floor", [](const nlohmann::json& j){ return j.is_number_integer(); });
    std::vector<int> distancesVect = getJsonVec<int>(obj, "distances", [](const nlohmann::json& j){ return j.is_number_integer(); });
    std::vector<int> connectedNodes = getJsonVec<int>(obj, "connected", [](const nlohmann::json& j){ return j.is_number_integer(); });

    return Node(id, distancesVect, connectedNodes, floor, X, Y);
}

void JSONReader::createClassrooms(const json &obj, Node &node) const
{
    std::vector<json> classroomsVec = getJsonVec<json>(obj, "classrooms", [](const nlohmann::json& j){ return j.is_object(); });
    for (const auto &classroom : classroomsVec)
    {
        std::string name = getJsonValue<std::string>(classroom, "name", [](const nlohmann::json& j){ return j.is_string(); });
        std::string description = getJsonValue<std::string>(classroom, "description", [](const nlohmann::json& j){ return j.is_string(); });
        Classroom Class(name, description);
        node.addClassroom(Class);
    }
}

void JSONReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
    }
}
