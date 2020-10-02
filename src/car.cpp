#include "car.h"

void Car::printSeatManifest()
{
    printf("%s\n", CarToString(m_Color, m_Type).c_str());
    for (Seat* seat : m_Seats)
    {
        printf("\t - %s%s\n", SeatTypeToString(seat->type).c_str(), seat->personInSeat.GetName().c_str());      //
    }
}

void Car::printCarReservationInfo()
{
    printf("%s\n", CarToString(*this).c_str());
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
    m_Seats.push_back(new Seat(SeatType::DRIVER));              //determines each seat in the sedan, sets hierarchy (how they're dislayed in console)
    m_Seats.push_back(new Seat(SeatType::FRONT));
    m_Seats.push_back(new Seat(SeatType::SIDE));
    m_Seats.push_back(new Seat(SeatType::MIDDLE));
    m_Seats.push_back(new Seat(SeatType::SIDE));
    
}

Compact::Compact(CarColor color)
    : Car(CarType::COMPACT, color)
{
    m_Seats.push_back(new Seat(SeatType::DRIVER));              //determines each seat in the compact, sets hierarchy
    m_Seats.push_back(new Seat(SeatType::FRONT));
    m_Seats.push_back(new Seat(SeatType::BACK));
    m_Seats.push_back(new Seat(SeatType::BACK));   
}

Pickup::Pickup(CarColor color)
    : Car(CarType::PICKUP, color)
{
    m_Seats.push_back(new Seat(SeatType::DRIVER));              //determines each seat in the truck, sets hierarchy
    m_Seats.push_back(new Seat(SeatType::FRONT));
}

std::string CarToString(CarColor color, CarType type) 
{
    std::string result;

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

std::string CarToString(Car car) 
{ 
    return CarToString(car.getColor(), car.getType());
}

std::string SeatToString(SeatType seat)
{
    switch(seat)                                               //for visuals of car to show what seats are available/taken/driver and how much if they're available
    {
        case(SeatType::TAKEN):   return "(T) ";
        case(SeatType::DRIVER): return "(D) ";
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