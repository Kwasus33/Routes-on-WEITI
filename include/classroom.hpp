#include <iostream>

class Classroom
{
public:
    Classroom();
    Classroom(std::string name);
    Classroom(std::string name, std::string description);
    std::string getName() const;
    std::string getDescription() const;
    void setName(std::string &newName);
    void setDescription(std::string newDescription);

private:
    std::string description;
    std::string name;
};