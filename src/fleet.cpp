/*
Filename: fleet.cpp
-------------------------------------------------------
Developers: Taylor Hess & Kevin Miller
Class Name: Computational Problem Solving II (CPET-321)
Academic Term: Fall 2020-21
*/

#include "pch.h"
#include "fleet.h"

Fleet::Fleet()                                               
{
    m_Fleet.push_back(new Pickup(CarColor::PURPLE));        
    m_Fleet.push_back(new Compact(CarColor::RED));
    m_Fleet.push_back(new Compact(CarColor::BLUE));
    m_Fleet.push_back(new Compact(CarColor::YELLOW));
    m_Fleet.push_back(new Sedan(CarColor::BLUE));
    m_Fleet.push_back(new Sedan(CarColor::GREEN));

    m_ReserveSeats = getPassengerSeats();
}

// All fleet functions return a vector full of pointers, no copies

std::vector<Seat*> Fleet::getAllSeats()
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


std::vector<Car*> Fleet::getCars(CarType type)
{
    std::vector<Car*> result;
    for (Car* car : m_Fleet)
    {
        if (car->getType() == type)
        {
            result.push_back(car);
        }
    }

    return result;
}

std::vector<Seat*> Fleet::getSeats(CarType type)
{
    std::vector<Seat*> result = std::vector<Seat*>();
    for (Car* car : m_Fleet)
    {
        if (type == CarType::ALL || car->getType() == type)
        {
            for (Seat* seat : car->getSeats())
            {
                if (seat->type == SeatType::DRIVER)
                {
                    continue;
                }
                result.push_back(seat);
            }
        }
    }

    return result;
}

std::tuple<std::string, std::string, std::string> printCarHelper(Car* car)
{
    std::string out[3];
    out[0] = CarToString(car->getColor(), CarType::NONE);
    //front row
    int i = 0;
    int curLine = 1;
    for (Seat* seat : car->getSeats())
    {
        if (i == 2) 
        {
            curLine = 2;
        }

        if (seat->taken)
        {
            out[curLine] += SeatToString(SeatType::TAKEN);
        }
        else
        {
            out[curLine] += SeatToString(seat->type);
        }
        
        i++;
    }

    return std::make_tuple(out[0], out[1], out[2]);

}

//TODO (Kevin): Make this not so terrible
void Fleet::printReservationVisual(CarType type)
{

    std::vector<Car*> pickups = getCars(CarType::PICKUP);
    std::vector<Car*> compacts = getCars(CarType::COMPACT);
    std::vector<Car*> sedans = getCars(CarType::SEDAN);

    const uint32_t maxInCategory = std::max({pickups.size(), compacts.size(), sedans.size()});
    std::string out[2 + 3 * 3];

    switch(type)
    {
        case(CarType::PICKUP):
        {
            out[0] = "     Pickup";
            out[1] = "    --------";
            break;
        }
        case(CarType::COMPACT):
        {
            out[0] = "    Compacts";
            out[1] = "    --------";
            break;
        }
        case(CarType::SEDAN):
        {
            out[0] = "     Sedans";
            out[1] = "     ------";
            break;
        }
        case(CarType::ALL):
        {
            out[0] = "      Pickup      Compacts       Sedans";
            out[1] = "     --------     --------       ------";
            break;
        }
        default:
        {
            out[0] = "";
            out[1] = "";
            break;
        }
    }

    int curCarRow = 0;
    int curCar = 0;

    for (int curCarRow = 2; curCarRow < maxInCategory * 3 + 2; curCarRow += 3)
    {
        out[curCarRow]     += "   ";
        out[curCarRow + 1] += "   ";
        out[curCarRow + 2] += "   ";

        if (type == CarType::PICKUP || type == CarType::ALL)
        {
            if (curCar < pickups.size())
            {
                auto pickupOut = printCarHelper(pickups[curCar]);
                out[curCarRow]     += "  ";
                out[curCarRow]     += std::get<0>(pickupOut);
                out[curCarRow + 1] += std::get<1>(pickupOut);
                out[curCarRow + 2] += std::get<2>(pickupOut);
                out[curCarRow]     += "     ";
                out[curCarRow + 1] += "   ";
                out[curCarRow + 2] += "             ";
            }
            else
            {
                out[curCarRow]     += "            ";
                out[curCarRow + 1] += "             ";
                out[curCarRow + 2] += "             ";
            }
        }

        if (type == CarType::COMPACT || type == CarType::ALL)
        {
            if (curCar < compacts.size())
            {
                auto compactsOut = printCarHelper(compacts[curCar]);
                out[curCarRow]     += "   ";
                out[curCarRow] += std::get<0>(compactsOut);
                out[curCarRow + 1] += std::get<1>(compactsOut);
                out[curCarRow + 2] += std::get<2>(compactsOut);
                out[curCarRow]     += "       ";
                out[curCarRow + 1] += "    ";
                out[curCarRow + 2] += "    ";
            }
            else
            {
                out[curCarRow]     += "                 ";
                out[curCarRow + 1] += "                  ";
                out[curCarRow + 2] += "                  ";
            }
        }

        if (type == CarType::SEDAN || type == CarType::ALL)
        {
            if (curCar < sedans.size())
            {
                auto sedansOut = printCarHelper(sedans[curCar]);
                out[curCarRow]     += "    ";
                out[curCarRow + 2] += "\b\b";
                out[curCarRow] += std::get<0>(sedansOut);
                out[curCarRow + 1] += std::get<1>(sedansOut);
                out[curCarRow + 2] += std::get<2>(sedansOut);
                out[curCarRow]     += "   ";
                out[curCarRow + 1] += "   ";
                out[curCarRow + 2] += "   ";
            }
            else
            {
                out[curCarRow]     += "                ";
                out[curCarRow + 1] += "                ";
                out[curCarRow + 2] += "                ";
            }
        }

        curCar++;
    }

    for (int i = 0; i < 2 + 3 * 3; i++)
    {
        printf("%s\n", out[i].c_str());
    }
}

void Fleet::printManifest()
{
    for (Car* car : m_Fleet)
    {
        car->printSeatManifest();
    }
}


void Fleet::printManifestToFile()
{

    std::ofstream outFile;
    outFile = std::ofstream("data/all_reservations.txt");
    
    for (Car* car : m_Fleet)
    {
        car->printSeatManifestToFile(false);
    }
}