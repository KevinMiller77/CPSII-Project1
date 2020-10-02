#pragma once
#include "car.h"

class Fleet
{
public:
    Fleet();
    void printFullReservationInfo();

    std::vector<Seat*> getSeats();
    std::vector<Seat*> getDriverSeats();
    std::vector<Seat*> getPassengerSeats();

private:
    std::vector<Car*> m_Fleet;
};