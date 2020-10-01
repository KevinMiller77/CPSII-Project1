#pragma once

#include <string>
#include <vector>

#include "person.h"

//Colors of the car
enum class CarColor
{
    NONE = 0, PURPLE, RED, BLUE, YELLOW, GREEN
};

//Type of car, equals the number of seats
enum class CarType
{
    NONE = 0, PICKUP = 1, COMPACT = 3, SEDAN = 4
};

//Type of seat, equals number of credits
enum class SeatType
{
    NONE = 0, FRONT = 5, BACK = 3, SIDE = 2, MIDDLE = 1
};

//Actual seat, can be taken or not
struct Seat
{
    Seat(SeatType Type) : type(Type), cost((int)Type) {}

    SeatType type;
    unsigned int cost;
    Person personInSeat = Person();
    bool taken = false;
};

std::string CarToString(CarColor color, CarType car)
{
    std::string result;

    switch(color)
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

    switch(car)
    {
        case(CarType::NONE): result += " No Car"; break;
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

std::string SeatToString(SeatType seat)
{
    switch(seat)
    {
        case(SeatType::NONE):   return "(-) ";
        case(SeatType::FRONT):  return "(5) ";
        case(SeatType::BACK):   return "(3) ";
        case(SeatType::SIDE):   return "(2) ";
        case(SeatType::MIDDLE): return "(1) ";

        default: 
        {
            return "(?) ";
        }
    }
}

std::string SeatTypeToString(SeatType seat)
{
    switch(seat)
    {
        case(SeatType::NONE):   return " ";
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

class Car
{
public:
    Car(CarType type, CarColor color) : m_Type(type), m_Color(color) {}

    void printSeatManifest()
    {
        printf("%s\n", CarToString(m_Color, m_Type).c_str());
        for (Seat seat : m_Seats)
        {
            printf("\t - %s%s\n", SeatTypeToString(seat.type).c_str(), seat.personInSeat.GetName().c_str());
        }
    }

    CarColor getColor() { return m_Color; }
    CarType getType() { return m_Type; }
    std::vector<Seat>* getSeats() { return &m_Seats; }
    std::vector<Seat>* getFreeSeats()
    {
        std::vector<Seat>* result = new std::vector<Seat>;

        for (Seat seat : m_Seats)
        {
            if (!seat.taken) result->push_back(seat);
        }

        return result;
    }
    

protected:
    CarType m_Type;
    CarColor m_Color;
    std::vector<Seat> m_Seats;
};

class Sedan : public Car
{
public:
    Sedan(CarColor color)
        : Car(CarType::SEDAN, color)
    {
    }
};

class Compact : public Car
{
public:
    Compact(CarColor color)
        : Car(CarType::COMPACT, color)
    {
    }
};

class Pickup : public Car
{
public:
    Pickup(CarColor color)
        : Car(CarType::PICKUP, color)
    {
    }
};

