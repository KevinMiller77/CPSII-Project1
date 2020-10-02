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

    std::vector<Person> people = readDatabaseIntoVec(DATABASE_PATH);        //reads from given file of names
    std::vector<Seat*> driverSeats = flt.getDriverSeats();
    for (int i = 0; i < NUM_CARS; i++)                                      //the first 6 people from the list get assigned to driver status, hence the loop
    {
        driverSeats[i]->personInSeat = people[i];
    }

    std::vector<Seat*> passeats = flt.getPassengerSeats();                  //anything that's not a driver



    // Everything below here is tests    
    std::vector<Seat*> seats = flt.getSeats();                              // Grab all seats including drivers
    
    //manual test of a specific person
    passeats[2]->personInSeat = people[7];
    passeats[2]->taken = true;

    for (int i = 1; i <= seats.size(); i++)                                 //lists what seat, if someones in it, and how much it's worth
    {
        printf("Seat %d\t Name: %s\tCost: %d\n", i, seats[i - 1]->personInSeat.GetName().c_str(), seats[i - 1]->cost);
    }

    flt.printFullReservationInfo();                                                //Visually prints manifest (each car with visible seats)

    printf("Saving to temp db to test func...\n");
    saveToDatabase("data/temp.dat", people);

    return 0;
}