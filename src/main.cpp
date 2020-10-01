/*
Filename: main.cpp
-------------------------------------------------------
Developers: Taylor Hess & Kevin Miller
Class Name: Computational Problem Solving II (CPET-321)
Academic Term: Fall 2020-21
*/

#include <stdio.h>
#include "utils.h"

#define DATABASE_PATH "data/quidditch_team.dat"

//Test main to make sure the build system works
int main(int argv, char** argc)
{
    std::vector<Person> people = readDatabaseIntoVec(DATABASE_PATH);

    for (Person peep : people)
    {
        printf("Person: %s, Credits %d, Driver? %s\n", peep.GetName().c_str(), peep.GetCredits(), peep.IsDriver() ? "Yes" : "No");
    }

    saveToDatabase("data/temp.dat", people);

    return 0;
}