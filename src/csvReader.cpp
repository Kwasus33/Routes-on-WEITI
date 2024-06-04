#include "csvReader.hpp"


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

    for(const std::string& path: pathsVec)
    {
        std::ifstream fp_in(path);
        isReadPathValid(fp_in);

        while (!fp_in.eof())
        {
            fp_in >> line1;
            if (!fp_in.eof()){
                fp_in >> line2;
            }
            
            if (!fp_in.eof()){
                fp_in >> line3;
            }

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

        for (size_t i = 0; i < values.size(); i += 2)
        {
            int key = ++i;
            Classroom Class(values.at(i), values.at(key));
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
    if (!fp.is_open()){
        std::cerr << "Failed to open file" << std::endl;
    }
}
