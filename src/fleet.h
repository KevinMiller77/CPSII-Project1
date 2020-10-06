#pragma once
#include "car.h"

class Fleet
{
public:
    Fleet();
    void printReservationVisual(CarType type = CarType::ALL);
    void printManifest();
    void printManifestToFile();

    std::vector<Seat*> getAllSeats();
    std::vector<Seat*> getDriverSeats();
    std::vector<Seat*> getPassengerSeats();

    std::vector<Car*> getCars(CarType type);
    std::vector<Seat*> Fleet::getSeats(CarType type);



private:
    std::vector<Car*> m_Fleet;
    std::vector<Seat*> m_ReserveSeats;
};