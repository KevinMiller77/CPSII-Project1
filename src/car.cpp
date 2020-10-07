/*
Filename: car.cpp
-------------------------------------------------------
Developers: Taylor Hess & Kevin Miller
Class Name: Computational Problem Solving II (CPET-321)
Academic Term: Fall 2020-21
*/

#include "pch.h"
#include "car.h"

void Car::printSeatManifest()
{
    printf("%s\n", CarToString(m_Color, m_Type).c_str());
    for (Seat* seat : m_Seats)
    {
        printf("  - %s%s\n", SeatTypeToString(seat->type).c_str(), seat->personInSeat->GetName().c_str());
    }
}

void Car::printSeatManifestToFile(bool individualManifest)
{
    std::string fileName = individualManifest ? "data/" + CarToString(m_Color, m_Type) + ".txt" : "data/all_reservations.txt";
    
    std::ofstream outFile;
    if (individualManifest)
    {
        outFile = std::ofstream(fileName.c_str());
    }
    else
    {
        outFile = std::ofstream(fileName.c_str(), std::ofstream::out | std::ofstream::app);
    }

    if (!outFile)
    {
        printf("There was a problem opening file for car manifest write!!!\n");
        return;
    }

    outFile << CarToString(m_Color, m_Type).c_str() << std::endl;
    for (Seat* seat : m_Seats)
    {
        outFile << "  - " << SeatTypeToString(seat->type).c_str() << seat->personInSeat->GetName().c_str() << std::endl;
    }

    outFile.close();
}

void Car::printCarReservationInfo()
{
    printf("%s\n", CarToString(m_Color, CarType::NONE).c_str());
    //front row
    int i = 0;
    for (Seat* seat : m_Seats)
    {
        if (i == 2) 
        {
            printf("\n");
        }

        if (seat->taken)
        {
            printf(SeatToString(SeatType::TAKEN).c_str());
        }
        else
        {
            printf(SeatToString(seat->type).c_str());
        }
        
        i++;
    }
    printf("\n\n");
}

std::vector<Seat*> Car::getFreeSeats()
{
    std::vector<Seat*> result;

    for (Seat* seat : m_Seats)
    {
        if (!seat->taken) result.push_back(seat);
    }

    return result;
}

Sedan::Sedan(CarColor color)
    : Car(CarType::SEDAN, color)
{
    m_Seats.push_back(new Seat(SeatType::DRIVER , this));              //determines each seat in the sedan, sets hierarchy (how they're dislayed in console)
    m_Seats.push_back(new Seat(SeatType::FRONT  , this));
    m_Seats.push_back(new Seat(SeatType::SIDE   , this));
    m_Seats.push_back(new Seat(SeatType::MIDDLE , this));
    m_Seats.push_back(new Seat(SeatType::SIDE   , this));
    
}

Compact::Compact(CarColor color)
    : Car(CarType::COMPACT, color)
{
    m_Seats.push_back(new Seat(SeatType::DRIVER , this));              //determines each seat in the compact, sets hierarchy
    m_Seats.push_back(new Seat(SeatType::FRONT  , this));
    m_Seats.push_back(new Seat(SeatType::BACK   , this));
    m_Seats.push_back(new Seat(SeatType::BACK   , this));   
}

Pickup::Pickup(CarColor color)
    : Car(CarType::PICKUP, color)
{
    m_Seats.push_back(new Seat(SeatType::DRIVER, this));              //determines each seat in the truck, sets hierarchy
    m_Seats.push_back(new Seat(SeatType::FRONT , this));
}

std::string CarToString(CarColor color, CarType type) 
{
    std::string result = std::string();

    switch(color)                                               //allows for a switch of car color
    {
        case(CarColor::NONE):   result = ""; break;
        case(CarColor::PURPLE): result = "Purple"; break;
        case(CarColor::RED):    result = "Red"; break;
        case(CarColor::BLUE):   result = "Blue"; break;
        case(CarColor::YELLOW): result = "Yellow"; break;
        case(CarColor::GREEN):  result = "Green"; break;
        default: 
        {
            result = "Unknown Color";
        }
    }

    switch(type)                                               //allows for a switch of car type (similar to color)
    {
        case(CarType::NONE): result += ""; break;
        case(CarType::PICKUP): result += " Pickup"; break;
        case(CarType::COMPACT): result += " Compact"; break;
        case(CarType::SEDAN): result += " Sedan"; break;
        default:
        {
            result += "Unknown Car Type";
        }
    }

    return result;
}

std::string CarToString(Car car) 
{ 
    return CarToString(car.getColor(), car.getType());
}

std::string SeatToString(SeatType seat)
{
    switch(seat)                                               //for visuals of car to show what seats are available/taken/driver and how much if they're available
    {
        case(SeatType::TAKEN):   return " (T) ";
        case(SeatType::DRIVER): return " (D) ";
        case(SeatType::FRONT):  return " (5) ";
        case(SeatType::BACK):   return " (3) ";
        case(SeatType::SIDE):   return " (2) ";
        case(SeatType::MIDDLE): return " (1) ";

        default: 
        {
            return "(?) ";
        }
    }
}

std::string SeatTypeToString(SeatType seat)
{
    switch(seat)                                               //specifies seat type, helper function (may not be used)
    {
        case(SeatType::TAKEN):   return " ";
        case(SeatType::DRIVER):  return "Driver: ";
        case(SeatType::FRONT):  return "Front: ";
        case(SeatType::BACK):   return "Back: ";
        case(SeatType::SIDE):   return "Back-Side: ";
        case(SeatType::MIDDLE): return "Back-Middle: ";

        default: 
        {
            return "(?) ";
        }
    }
}