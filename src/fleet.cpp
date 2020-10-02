#include "fleet.h"

Fleet::Fleet()                                               
{
    m_Fleet.push_back(new Pickup(CarColor::PURPLE));        
    m_Fleet.push_back(new Compact(CarColor::RED));
    m_Fleet.push_back(new Compact(CarColor::BLUE));
    m_Fleet.push_back(new Compact(CarColor::YELLOW));
    m_Fleet.push_back(new Sedan(CarColor::BLUE));
    m_Fleet.push_back(new Sedan(CarColor::GREEN));
}

// All fleet functions return a vector full of pointers, no copies


std::vector<Seat*> Fleet::getSeats()
{
    std::vector<Seat*> seats;
    for (Car* car : m_Fleet)
    {
        std::vector<Seat*> carsSeats = car->getSeats();
        seats.insert(seats.end(), carsSeats.begin(), carsSeats.end());
    }
    
    return seats;
}

std::vector<Seat*> Fleet::getPassengerSeats()
{
    std::vector<Seat*> seats;
    for (Car* car : m_Fleet)
    {
        std::vector<Seat*> carsSeats = car->getSeats();
        seats.insert(seats.end(), carsSeats.begin() + 1, carsSeats.end());
    }
    
    return seats;
}

std::vector<Seat*> Fleet::getDriverSeats()
{
    std::vector<Seat*> seats;
    for (Car* car : m_Fleet)
    {
        if (car->getSeats().size() > 1)
        {
            
            std::vector<Seat*> carsSeats = car->getSeats();
            seats.insert(seats.end(), carsSeats.begin(), carsSeats.begin() + 1);
        }
    }
    
    return seats;
}

void Fleet::printFullReservationInfo()
{
    for (Car* car : m_Fleet)
    {
        car->printCarReservationInfo();
    }
}