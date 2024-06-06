#include "csvReader.hpp"

/////   CSV reader - more prone to errors

//      csv konwencja zapisu:
//      id,x,y,floor,
//      distance,connected,distance,connected...
//      name,description,name,description...    -classrooms

CSVReader::CSVReader() : FileReader(){};

CSVReader::CSVReader(const std::vector<std::string> &pathsVec) : FileReader(pathsVec){};

Graph CSVReader::readDataIntoGraph() const
{
    Graph graph;
    std::string line1;
    std::string line2;
    std::string line3;

    for (const std::string &path : pathsVec)
    {
        std::ifstream fp_in(path);
        isReadPathValid(fp_in);
        while (!fp_in.eof())
        {
            getline(fp_in, line1);
            if (!fp_in.eof())
            {
                getline(fp_in, line2);
            }

            if (!fp_in.eof())
            {
                getline(fp_in, line3);
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

Node CSVReader::addNode(std::string &line1, std::string &line2, std::string &line3) const
{
    Node node = createNode(line1, line2);
    createClassrooms(line3, node);
    return node;
};

std::vector<std::string> CSVReader::readLine(const std::string& line) const
{
    std::vector<std::string> values;

    std::size_t start = 0;
    std::size_t end = line.find(',');

    while (end != std::string::npos)
    {
        values.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find(',', start);
    }
    values.push_back(line.substr(start));

    return values;
}

Node CSVReader::createNode(const std::string &line1, const std::string &line2) const
{
    int id, X, Y, floor;
    std::vector<int> distances;
    std::vector<int> connected; 
    
    try
    {   
        std::vector<std::string> values = readLine(line1);

        id = stoi(values.at(0));
        X = stoi(values.at(1));
        Y = stoi(values.at(2));
        floor = stoi(values.at(3));

        values.clear();
        values = readLine(line2);

        for (std::size_t i = 0; i < values.size(); i += 1)
        {
            int key = i+1;
            if (values.at(i).empty() || values.at(key).empty())
            {
                continue;
            }
            else
            {
                distances.push_back(stoi(values.at(i)));
                connected.push_back(stoi(values.at(key)));
            }
        }
    }

    catch (const std::invalid_argument &error)
    {
        throw error;
    }

    catch (const std::out_of_range &error)
    {
        throw error;
    }

    return Node(id, distances, connected, floor, X, Y);
}

void CSVReader::createClassrooms(const std::string &line3, Node &node) const
{
    try
    {
        std::vector<std::string> values = readLine(line3);

        for (size_t i = 0; i < values.size(); i += 2)
        {
            int key = i+1;
            Classroom Class(values.at(i), values.at(key));
            node.addClassroom(Class);
        }
    }

    catch (const std::invalid_argument &error)
    {
        throw error;
    }

    catch (const std::out_of_range &error) // for .at() method
    {
        throw error;
    }
}

void CSVReader::isReadPathValid(const std::ifstream &fp) const
{
    if (!fp.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
        throw std::invalid_argument("Invalid file path");
    }
}
