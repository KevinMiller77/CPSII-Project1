#pragma once
/*
Filename: fleet.h
-------------------------------------------------------
Developers: Taylor Hess & Kevin Miller
Class Name: Computational Problem Solving II (CPET-321)
Academic Term: Fall 2020-21
*/

#include "pch.h"
#include "car.h"

// A collection of cars that drive together
// a.k.a. A fleets
class Fleet
{
public:

    Fleet();

    //Print the nice reservation visual to the console
    void printReservationVisual(CarType type = CarType::ALL);

    // Print full maifest to the console 
    void printManifest();

    // Print full manifest the the all_reservations file
    // Admin password protected
    void printManifestToFile();

    //The fucntion names describe themselves
    std::vector<Seat*> getAllSeats();
    std::vector<Seat*> getDriverSeats();
    std::vector<Seat*> getPassengerSeats();

    std::vector<Car*> getCars(CarType type);
    std::vector<Seat*> getSeats(CarType type);

private:
    std::vector<Car*> m_Fleet;

    // This is a nice vector to have, once all cars have 
    // Been created, we grab their Seat*s and 
    // Accumulate them into here for clean linear 
    // time access for getters
    std::vector<Seat*> m_ReserveSeats;
};