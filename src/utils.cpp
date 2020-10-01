#include "utils.h"

std::vector<Person> readDatabaseIntoVec(std::string filepath)
{
    std::vector<Person> result = std::vector<Person>();

    std::ifstream dbFile;

    dbFile.open(filepath.c_str());

    if (!dbFile)
    {
        printf("Could not open database file for READING!!\n");
        return result;
    }

    //Grab the drivers and passengers from the file
    for (std::string line; std::getline(dbFile, line); )
    {
        int intermediate_sp = line.find(" ");
        int space = line.find(" ", intermediate_sp + 1);
        
        //Person is a driver
        if (space == -1)
        {
            result.push_back(Person(line, -1));
        }
        else
        {
            std::string name = line.substr(0, space);
            int credits = std::stoi(line.substr(space));
            result.push_back(Person(name, credits, false));
        }
    }

    return result;   
}


void saveToDatabase(std::string filepath, std::vector<Person>& people)
{
    std::ofstream dbFile;

    dbFile.open(filepath.c_str());

    if (!dbFile)
    {
        printf("Could not open database file for WRITING!!\n");
        return;
    }

    for (Person peep : people)
    {
        std::string credits;
        if (peep.IsDriver())
        {
            credits = " ";
        }
        else
        {
            credits = std::to_string(peep.GetCredits());
        }
        
        dbFile << peep.GetName().c_str() << " " << credits.c_str() << std::endl;
    }
}