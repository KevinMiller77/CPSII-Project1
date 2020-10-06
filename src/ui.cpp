#include "ui.h"

UI::UI()
{
    //Setup the fleet (Most is done in constructors)
    m_Fleet = Fleet();

    //Get our people
    m_People = readDatabaseIntoVec(DATABASE_PATH);        
    m_DriverSeats = m_Fleet.getDriverSeats();

    //Populat our driver seats
    for (int i = 0; i < NUM_CARS; i++) 
    {
        m_DriverSeats[i]->personInSeat = m_People[i];
    }
    
    //Grab our other seats for easy reference.
    //REMEMEBER! All of the vectors are full of pointers
    //          That means no copies and cross use!
    m_PassengerSeats = m_Fleet.getPassengerSeats();                  
    m_AllSeats = m_Fleet.getAllSeats();
}

void UI::run()
{
    //Start the UI
    while(!mainLoop()) {}
}

//Simpply prompts the user for a certain reservation number
//Returns 0 if and only if there was a problem getting input
//Should never return a number above 18
uint32_t reservationSelectionHelper()
{
    printf("Enter reservation number to modify\n");
    uint32_t idx;
    std::cin >> idx;
    if (idx < 1 || idx > 18)
    {
        return 0;
    }
    return idx;
}

bool UI::mainLoop()
{
    CLEAR_SCR();
    printf("Welcome to the Carpool Manager!\n");
    printf("Please enter your desired action below...\n\n");
    printf("(C)     Create a reservation\n");
    printf("(M)     Modify a reservation\n");
    printf("(D)     Delete a reservation\n");
    printf("(L)     Display vehicles\n");
    printf("(P)     Print vehicle assignments to a file named after the car\n");
    printf("(A)     Print All reservations\n\n");
    printf("(E)     Exit NOTE: If you do not exit through this method, the database will not update!!\n\n > ");

    char command;
    std::cin >> command; 
    command = tolower(command);

    switch(command)
    {
        case('c'):
        {
            if (!Create())
            {
                printf("\n\nCould not create!\nPress enter to start over...\n");
                WAIT_FOR_ENTER();
                return false;
            }
            break;
        }
        case('m'):
        {
            CLEAR_SCR();
            uint32_t idx = reservationSelectionHelper();
            //Destroy failed
            if (idx == 0 || !Destroy(idx))
            {
                printf("\n\nInvalid option!! Seat was either empty or you input an invalid reservation ID\nPress enter to start over...\n");
                WAIT_FOR_ENTER();
                return false;
            }
            if (!Create())
            {
                printf("\n\nInvalid option!! All options were occupied or your input was invalid\nPress enter to start over...\n");
                WAIT_FOR_ENTER();
                return false;
            }
            break;
        }
        case('d'):
        {
            CLEAR_SCR();
            uint32_t idx = reservationSelectionHelper();
            //Destroy failed
            if (idx == 0 || !Destroy(idx))
            {
                printf("\n\nInvalid option!! Seat was either empty or you input an invalid reservation ID\nPress enter to start over...\n");
                WAIT_FOR_ENTER();
                return false;
            }
            break;
        }
        case('l'):
        {
            CLEAR_SCR();
            CLEAR_CIN();

            m_Fleet.printReservationVisual();
            printf("\n\nPress enter to return to main menu...\n");
            WAIT_FOR_ENTER();
            break;
        }
        case('p'):
        {
            printf("Please enter the car color and type. Ex. Purple Pickup\n\n > ");
            CLEAR_CIN();
            std::vector<std::string> words = *WordsFromInput();

            try
            {
                CarColor col = s_Keys.Color.at(words[0]);
                try
                {

                    CarType type = s_Keys.Car.at(words[1]);

                    for (Car* car : m_Fleet.getCars(type))
                    {
                    if (car->getColor() == col)
                        {
                            car->printSeatManifestToFile();
                            printf("\nSuccessfully printed car info to a file.\n");
                            printf("\n\nPress enter to return to main menu...\n");
                            WAIT_FOR_ENTER();
                            return false;
                        }
                    }
                }
                catch (const std::exception& e)
                {
                    printf("\n\nInvalid option!!\nPress enter to start over...\n");
                    WAIT_FOR_ENTER();
                    return false;
                }
            }
            catch(const std::exception& e)
            {
                printf("\n\nInvalid option!!\nPress enter to start over...\n");
                WAIT_FOR_ENTER();
                return false;
            }
            

            break;
        }
        case('a'):
        {
            printf("Please enter password\n\n > ");
            int pass;
            std::cin >> pass;

            if (pass == TERMINAL_PASSWORD)
            {
                m_Fleet.printManifestToFile();
                printf("Hello admin!\nSuccessfully printed car info to a file.\n");
                printf("\n\nPress enter to return to main menu...\n");
                WAIT_FOR_ENTER();
                return false;
            }
            else
            {
                printf("Sorry, wrong password.\n");
                printf("\n\nPress enter to return to main menu...\n");
                WAIT_FOR_ENTER();
                return false;
            }
            
            break;
        }
        case('e'):
        {
            saveToDatabase(DATABASE_PATH, m_People);
            return true;
            break;
        }
        default:
        {
            printf("\n\nInvalid option!!\nPress enter to start over...\n");
            WAIT_FOR_ENTER();
        }      
    }

    return false;
}

std::vector<std::string>* UI::WordsFromInput()
{
    std::string input;  //""
    std::getline(std::cin, input);

    //Convert string to lowercase
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){ return std::tolower(c); });

    //split input into a vector of "words"
    std::vector<std::string>* words = new std::vector<std::string>;

    {
        std::istringstream split (input);
        for (std::string tempGrab; std::getline(split, tempGrab, ' '); )
        {
            words->push_back(tempGrab);
        }
    }

    return words;
}

bool UI::Create()
{
    CLEAR_SCR();
    CLEAR_CIN();
    
    printf("\nWho is this seat for? First and last name please!\n\n > ");
    std::string personName;
    std::getline(std::cin, personName);
    int personIdx = GetPersonFromName(personName);
    Person* person = nullptr;
    if (personIdx != -1)
    {
        person = m_People[personIdx];
    }
    
    while (person == nullptr)
    {
        CLEAR_CIN();
        if (personName == "exit")
        {
            return false;
        }
        
        printf("The name you have entered is not in our database. Please enter your name again. Type \"exit\" to cancel\n\n > ");
        std::getline(std::cin, personName);
        personIdx = GetPersonFromName(personName);
        if (personIdx != -1)
        {
            person = m_People[personIdx];
        }
    }

    {
    int idx = 0;
    for (Seat* seat : m_Fleet.getPassengerSeats())
    {
        if (seat->personInSeat == person)
        {
            printf("You already have a reservation! Here is your info again\n");
            printf("Reservation info : \n - Name: % s\n - ReservationID: % d\n - Car: % s\n\n", person->GetName().c_str(), idx + 1, CarToString(*seat->parent).c_str());
            printf("Write down your ReservationID and press enter to continue");
            WAIT_FOR_ENTER();
            return true;
        }
        idx++;
    }

    }

    CLEAR_SCR();
    m_Fleet.printReservationVisual();

    printf("\n\nPlease select a vehicle type, color, or type of seat;\n\n");
    printf("Car types: Sedan, Truck, Compact\n");
    printf("Seat types: front, back, side, middle. Only sedans have a middle seat. \n");
    printf("Back can be chosen on sedans as well as compacts but in sedans you might get a side or middle, whichever is best.\n");
    printf("If you only select a seat type, you will be given the best available seat. \n");
    printf("   ie. entering \"Back\" will try for a compact back seat and resort to a sedan middle and then sedan side\n\n");
    printf("Enter no commas and seperate all words with spaces!!\nFormat should be one of the following\n");
    printf("   <Car Type>\n   <Seat>\n   <Car Type> <Seat>\n   <Color> <Car Type> <Seat>\n\n > ");


    
    std::vector<std::string> words = *WordsFromInput();
    
    //We never have more than 3 or less than 1 arguement
    if (words.size() > 3 || words.size() < 1)
    {
        return false;
    }

    CarType carType = CarType::NONE;
    CarColor carColor = CarColor::NONE;
    
    //Used driver seat because driver will never be used in this context and resolves to 0 
    SeatType seatType = SeatType::DRIVER; 
    
    //Now for the fun part, parsing
    //The try catches are because we want to throw an exception,
    //  if an unordered map has no member you're asking for, it throws

    Seat* seatToReserve = nullptr;
    
    //bool to check if the situation has already been handled to exit the loop
    bool handled = false;

    for (int i = 0; i < 3; i++)
    {
        if (handled) break;
        switch(i)
        {
            //Car Type, break out into carGiven() or find best seat in car type
            case(0):
            {
                try
                {
                    carType = s_Keys.Car.at(words[0]);
                    try
                    {
                        seatType = s_Keys.Pos.at(words[1]);
                        seatToReserve = getBestSeat(person->GetCredits(), seatType, carType); 
                        if (seatToReserve == nullptr)
                        {
                            return false;
                        }
                        handled = true;
                    }
                    catch(const std::exception& e)
                    {
                        //Only car type was given, show them the options
                        CLEAR_SCR();
                        m_Fleet.printReservationVisual(carType);
                        printf("\n\nPlease select a type of seat;\n\n");
                        printf("Seat type: front, back, side, middle. Only sedans have a middle seat. \n");
                        printf("Enter no commas and seperate all words with spaces!!\nFormat should be the following\n");
                        printf("   <Seat>\n\n > ");

                        std::vector<std::string> seatSelWords = *WordsFromInput();
                        if (seatSelWords.size() > 1)
                        {
                            return false;
                        }

                        try
                        {
                            seatType = s_Keys.Pos.at(seatSelWords[0]);
                            seatToReserve = getBestSeat(person->GetCredits(), seatType, carType); 
                            if (seatToReserve == nullptr)
                            {
                                return false;
                            }
                            handled = true;
                        }
                        catch(const std::exception& e)
                        {
                            return false;
                        }
                    }
                    

                }
                catch(const std::exception& e)
                {
                    //Not a car type keyword, do nothing
                }
                break;
            }
            //Seat type given first
            case(1):
            {
                try
                {
                    seatType = s_Keys.Pos.at(words[0]);
                    seatToReserve = getBestSeat(person->GetCredits(), seatType); 
                    if (seatToReserve == nullptr)
                    {
                        return false;
                    }
                    handled = true;
                }
                catch(const std::exception& e)
                {
                    //Not a seat type keyword, do nothing
                }
                break;
            }

            //Color first, meaning it has to be the full arg
            case(2):
            {
                try
                {
                    carColor = s_Keys.Color.at(words[0]);
                    try
                    {
                        carType = s_Keys.Car.at(words[1]);
                        seatType = s_Keys.Pos.at(words[2]);

                        for (Car* car : m_Fleet.getCars(carType))
                        {
                            if (car->getColor() == carColor)
                            {
                                bool canAfford = false;
                                //I hate nested for loops but this was simplist
                                for (Seat* seat : car->getSeats())
                                {
                                    if (seat->taken)
                                    {
                                        continue;
                                    }
                                    bool match = seat->type == seatType || ((carType == CarType::SEDAN && seatType == SeatType::BACK) && (seat->type == SeatType::MIDDLE || seat->type == SeatType::BACK));
                                    if (match && seat->cost <= person->GetCredits())
                                    {
                                        canAfford = true;
                                        seatToReserve = seat;
                                        handled = true;
                                        break;
                                    }
                                }

                                if (!canAfford) 
                                {
                                    printf("You cannot afford this seat!\n");
                                    return false;
                                }
                                    
                            }
                        }
                    }
                    catch(const std::exception& e)
                    {
                        return false;
                    }
                }
                catch(const std::exception& e)
                {
                    //None of the keywords were valid
                    return false;
                }
                break;
            }

            default:
            {
                break;
            }
        }
    }
    
    

    seatToReserve->personInSeat = person;
    seatToReserve->taken = true;
    int id = -1;

    for (int i = 0; i < m_PassengerSeats.size(); i++)
    {
        if (m_PassengerSeats[i] == seatToReserve)
        {
            id = i + 1;
        }
    }

    person->UseCredits(seatToReserve->cost);
    CLEAR_SCR();
    printf("You have successfully created your reservation.\n\nReservation info: \n - Name: %s\n - ReservationID: %d\n - Car: %s\n\n", person->GetName().c_str(), id, CarToString(*seatToReserve->parent).c_str());
    printf("Write down your ReservationID and press enter to continue");
    WAIT_FOR_ENTER();

    return true;
}

Seat* UI::getBestSeat(uint32_t credits, SeatType seatIN, CarType carIN)
{
    std::vector<Seat*> lookingSeats = m_Fleet.getSeats(carIN);
    
    //If the seat is back and theres a possiblility a sedan is involved,
    // we make a different loop to save time when it isnt a sedan
    if (seatIN == SeatType::BACK && (carIN == CarType::ALL || carIN == CarType::SEDAN))
    {
        Seat* bestFound = nullptr;

        //Start with driver because its worth   0
        SeatType bestsType = SeatType::DRIVER;

        //Reverse because sedan is always worst choice here and last no matter what
        std::reverse(lookingSeats.begin(), lookingSeats.end());    
        bool unaffordable = false;
        for (Seat* seat : lookingSeats)
        {
            if (seat->taken) 
            {
                continue;
            }
            if (seat->cost > credits)
            {
                unaffordable = true;
                continue;
            }

            if ((uint32_t)seat->type >= (uint32_t)bestsType && (uint32_t)seat->type <= (uint32_t)seatIN)
            {
                //Change best found open seat if better is found
                bestFound = seat;
                bestsType = seat->type;
            }
        }

        if (unaffordable)
        {
            printf("You cannot afford this seat!\n");
        }

        return bestFound;
    }

    for (Seat* seat : lookingSeats)
    {
        if (seat->taken || seat->cost > credits) 
        {
            continue;
        }

        if (seat->type == seatIN)
        {
            //Return seat if it wasn't taken and matched
            return seat;
        }
    }

    //Complete fail returns nullptr
    return nullptr;
}

int UI::GetPersonFromName(std::string& name)
{
    for (int i = 0; i < m_People.size(); i++)
    {
        if (m_People[i]->GetName() == name)
        {
            return i;
        }
    }

    return -1;
}


bool UI::Destroy(uint32_t reservationNumber)
{
    //Reservation number shoudl never enter this function if it is out of bounds!!!
    Seat seat = *m_PassengerSeats[reservationNumber - 1]; 
    if (!seat.taken)
    {
        return false;
    }

    seat.taken = false;
    seat.personInSeat = new Person();
    
    return true;
}

// void UI::DisplayVisual()
// {

// }
