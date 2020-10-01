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
    TAKEN = -1, DRIVER = 0, FRONT = 5, BACK = 3, SIDE = 2, MIDDLE = 1
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

class Car
{
public:
    Car(CarType type, CarColor color) : m_Type(type), m_Color(color) {}

    void printSeatManifest();
    void printCarReservationInfo();

    CarColor getColor() { return m_Color; }
    CarType getType() { return m_Type; }
    std::vector<Seat*> getSeats() { return m_Seats; }
    std::vector<Seat*> getFreeSeats();
    

protected:
    CarType m_Type;
    CarColor m_Color;
    std::vector<Seat*> m_Seats;
};

class Sedan : public Car
{
public:
    Sedan(CarColor color);
};

class Compact : public Car
{
public:
    Compact(CarColor color);
};

class Pickup : public Car
{
public:
    Pickup(CarColor color);
};


//String helper functions
std::string CarToString(CarColor color, CarType car);
std::string CarToString(Car car);
std::string SeatToString(SeatType seat);
std::string SeatTypeToString(SeatType seat);