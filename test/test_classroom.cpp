#include "classroom.hpp"
#include <gtest/gtest.h>

TEST(ClassroomTest, Constructors)
{
    Classroom class1;
    Classroom class2("Aula 131");
    Classroom class3("Aula 163", "PTCY");

    EXPECT_EQ(class1.getName(), "NO NAME");
    EXPECT_EQ(class1.getDescription(), "NO DESCRIPTION FOR THIS CLASSROOM");

    EXPECT_EQ(class2.getName(), "Aula 131");
    EXPECT_EQ(class2.getDescription(), "NO DESCRIPTION FOR THIS CLASSROOM");

    EXPECT_EQ(class3.getName(), "Aula 163");
    EXPECT_EQ(class3.getDescription(), "PTCY");
}