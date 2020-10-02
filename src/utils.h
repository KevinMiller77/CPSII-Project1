#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "person.h"

std::vector<Person> readDatabaseIntoVec(std::string filepath);                      //reads
void saveToDatabase(std::string filepath, std::vector<Person>& people);             //writes