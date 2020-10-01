/*
Filename: main.cpp
-------------------------------------------------------
Developers: Taylor Hess & Kevin Miller
Class Name: Computational Problem Solving II (CPET-321)
Academic Term: Fall 2020-21
*/

#include <stdio.h>
#include "fleet.h"
#include "utils.h"

#define NUM_CARS 6
#define DATABASE_PATH "data/quidditch_team.dat"

//Test main to make sure the build system works
int main(int argv, char** argc)
{
    Fleet flt = Fleet();

    std::vector<Person> people = readDatabaseIntoVec(DATABASE_PATH);
    std::vector<Seat*> driverSeats = flt.getDriverSeats();
    for (int i = 0; i < NUM_CARS; i++)
    {
        driverSeats[i]->personInSeat = people[i];
    }

    std::vector<Seat*> passeats = flt.getPassengerSeats();
    std::vector<Seat*> seats = flt.getSeats();
    
    passeats[2]->personInSeat = people[7];
    passeats[2]->taken = true;

    for (int i = 1; i <= seats.size(); i++)
    {
        printf("Seat %d\t Name: %s\tCost: %d\n", i, seats[i - 1]->personInSeat.GetName().c_str(), seats[i - 1]->cost);
    }

    flt.printFullManifest();

    printf("Saving to temp db to test func...\n");
    saveToDatabase("data/temp.dat", people);

    return 0;
}