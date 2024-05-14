#include <iostream>
#include "classroom.hpp"

Classroom::Classroom() : name("NO NAME"), description("NO DESCRIPTION FOR THIS CLASSROOM") {}

Classroom::Classroom(std::string name) : name(name), description("NO DESCRIPTION FOR THIS CLASSROOM") {}

Classroom::Classroom(std::string name, std::string description) : name(name), description(description) {}
std::string Classroom::getName() const
{
    return name;
}

std::string Classroom::getDescription() const
{
    return description;
}

void Classroom::setName(std::string &newName)
{
    name = newName;
}

void Classroom::setDescription(std::string newDescription)
{
    description = newDescription;
}