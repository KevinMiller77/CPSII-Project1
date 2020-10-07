#pragma once

/*
Filename: utils.h
-------------------------------------------------------
Developers: Taylor Hess & Kevin Miller
Class Name: Computational Problem Solving II (CPET-321)
Academic Term: Fall 2020-21
*/
#include "pch.h"

class Person;

std::vector<Person*> readDatabaseIntoVec(std::string filepath);                      //reads
void saveToDatabase(std::string filepath, std::vector<Person*>& people);             //writes