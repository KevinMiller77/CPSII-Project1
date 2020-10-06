#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "utils.h"
#include "fleet.h"

#define NUM_CARS 6
#define DATABASE_PATH "data/quidditch_team.dat"
#define CLEAR_CIN() { std::cin.clear(); std::cin.ignore(10000,'\n'); }
#define WAIT_FOR_ENTER() { int iReallyHateTheCPPstdSometimes = getchar();}
#define CLEAR_SCR() { if (system("CLS")) system("clear"); }

#define TERMINAL_PASSWORD 1234

struct Keys
{
    enum class Type
    {
        Car, Color, Pos
    };

    const std::unordered_map<std::string, CarType> Car = {  {"sedan",   CarType::SEDAN},\
                                                            {"pickup",  CarType::PICKUP},\
                                                            {"compact", CarType::COMPACT}};


    const std::unordered_map<std::string, SeatType> Pos = { {"front",   SeatType::FRONT},\
                                                            {"back",    SeatType::BACK},\
                                                            {"middle",  SeatType::MIDDLE},\
                                                            {"side",    SeatType::SIDE}};
 

    const std::unordered_map<std::string, CarColor> Color { {"purple",  CarColor::PURPLE}, \
                                                            {"red",     CarColor::RED},\
                                                            {"blue",    CarColor::BLUE},\
                                                            {"yellow",  CarColor::YELLOW},\
                                                            {"green",   CarColor::GREEN}};  

};

class UI
{
public:
    UI();
    ~UI() = default;
    void run();

private:
    // Retruns true if the program should end
    bool mainLoop();

    //Returns true if reservation is made 
    bool Create();
    Seat* getBestSeat(uint32_t credits, SeatType seatIN, CarType carIN = CarType::ALL);
    int GetPersonFromName(std::string& name);
    std::vector<std::string>* WordsFromInput();

    
    //Returns true if reservation is destroyed
    bool Destroy(uint32_t reservationNumber);

    void DisplayVisual();
    void Print(Car* car);

private:
    Fleet m_Fleet;
    Keys s_Keys;

    std::vector<Person*> m_People;
    std::vector<Seat*> m_AllSeats;
    std::vector<Seat*> m_PassengerSeats;
    std::vector<Seat*> m_DriverSeats;

};
