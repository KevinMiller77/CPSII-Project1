#pragma once
/*
Filename: application.h
-------------------------------------------------------
Developers: Taylor Hess & Kevin Miller
Class Name: Computational Problem Solving II (CPET-321)
Academic Term: Fall 2020-21
*/

#include "utils.h"
#include "fleet.h"

#define NUM_CARS 6
#define DATABASE_PATH "data/quidditch_team.dat"
#define CLEAR_CIN() { std::cin.clear(); std::cin.ignore(10000,'\n'); }
#define WAIT_FOR_ENTER() { int iReallyHateTheCPPstdSometimes = getchar();}
#define CLEAR_SCR() { if (system("CLS")) system("clear"); }

#define TERMINAL_PASSWORD 1234


class Application
{
public:
    Application();
    ~Application() = default;
    void run();

private:
    // Retruns true if the program should end
    bool mainLoop();

    //Returns true if reservation is made 
    bool Create();
    //Returns true if reservation is destroyed
    bool Destroy(uint32_t reservationNumber);

    //Given a SeatType and/or a CarType, find the best seat this person can have
    Seat* getBestSeat(uint32_t credits, SeatType seatIN, CarType carIN = CarType::ALL);
    //Given all properties of the Car, ie. Color, Make, Pos return the best seat
    Seat* getBestSeat(uint32_t credits, SeatType seatIN, CarType carIN, CarColor colorIN);

    //Helper to get a person given their name as a string
    int GetPersonFromName(std::string& name);
    // Returns a heap allocated vector a strings
    std::vector<std::string>* WordsFromInput();

    //Display the visual picker for all cars
    void DisplayVisual();
    

private:
    Fleet m_Fleet;

    std::vector<Person*> m_People;
    std::vector<Seat*> m_AllSeats;
    std::vector<Seat*> m_PassengerSeats;
    std::vector<Seat*> m_DriverSeats;

};
