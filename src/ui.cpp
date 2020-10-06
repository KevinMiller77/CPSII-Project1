#include "ui.h"


//Using a namespace to avoid global things
namespace Keys
{
    //Types of keywords we will encounter
    enum class KeyType
    {
        INVALID = 0, CAR = 1, COLOR = 2, SEAT = 3
    };

    const std::unordered_map<std::string, CarType> Car = {  {"sedan",   CarType::SEDAN},\
                                                            {"pickup",  CarType::PICKUP},\
                                                            {"compact", CarType::COMPACT}};


    const std::unordered_map<std::string, SeatType> Seat = { {"front",   SeatType::FRONT},\
                                                            {"back",    SeatType::BACK},\
                                                            {"middle",  SeatType::MIDDLE},\
                                                            {"side",    SeatType::SIDE}};
 

    const std::unordered_map<std::string, CarColor> Color { {"purple",  CarColor::PURPLE}, \
                                                            {"red",     CarColor::RED},\
                                                            {"blue",    CarColor::BLUE},\
                                                            {"yellow",  CarColor::YELLOW},\
                                                            {"green",   CarColor::GREEN}};  

    template <typename T>
    bool existsInMap(const std::unordered_map<std::string, T>& map, std::string& key)
    {
        return map.find(key) != map.end();
    }


    KeyType isValidKeyword(std::string& word)
    {
        if (existsInMap<CarType>(Car, word))
        {
            return KeyType::CAR;
        }
        else if (existsInMap<CarColor>(Color, word))
        {
            return KeyType::COLOR;
        }
        else if (existsInMap<SeatType>(Seat, word))
        {
            return KeyType::SEAT;
        }
        else
        {
            return KeyType::INVALID;
        }
    }
};




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
    printf("(A)     Print All reservations\n");
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
                printf("\n\nPress enter to start over...\n");
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
                printf("\n\nPress enter to start over...\n");
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
            printf("Reservation %d successfully removed!\n", idx);
            WAIT_FOR_ENTER();
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
                CarColor col = Keys::Color.at(words[0]);
                try
                {

                    CarType type = Keys::Car.at(words[1]);

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

//This function takes in a line, splits it, and spits out a heap allocated vector
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

//Function to create a reservation
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
            CLEAR_SCR();
            printf("Hello, %s!\n", person->GetName().c_str());
            printf("You already have a reservation! Here is your info again\n");
            printf("Reservation info : \n - ReservationID: % d\n - Car: % s\n\n", idx + 1, CarToString(*seat->parent).c_str());
            printf("Write down your ReservationID and press enter to continue");
            WAIT_FOR_ENTER();
            return true;
        }
        idx++;
    }

    }

    CLEAR_SCR();

    if (person->GetCredits() <= 0)
    {
        printf("Sorry, %s, You have run out of credits this week.\n", person->GetName().c_str());
        printf("We look forward to having you next week!");
        return false;
    }

    printf("\nHello, %s! You have %d credits.\n\n", person->GetName().c_str(), person->GetCredits());
    m_Fleet.printReservationVisual();

    printf("\n\nPlease select a vehicle type, color, or type of seat;\n");
    printf("Car types: Sedan, Truck, Compact\n");
    printf("Seat types: front, back, side, middle. Only sedans have a middle seat. \n");
    printf("Back can be chosen on sedans as well as compacts but in sedans you might get a side or middle, whichever is best.\n");
    printf("   ie. entering \"Back\" will try for a compact back seat and resort to a sedan middle and then sedan side\n\n");
    printf("!!Enter no commas and seperate all words with spaces!!\nFormat should be one of the following\n");
    printf("   <Car Type>\n   <Seat>\n   <Car Type> <Seat>\n   <Color> <Car Type> <Seat>\n > ");



    
    std::vector<std::string> words = *WordsFromInput();
    
    //We never have more than 3 or less than 1 arguement
    if (words.size() > 3 || words.size() < 1)
    {
        return false;
    }
    
    //Now for the fun part, parsing
    //The try catches are because we want to throw an exception,
    //  if an unordered map has no member you're asking for, it throws

    Seat* seatToReserve = nullptr;

    Keys::KeyType kw1 = Keys::KeyType::INVALID;
    Keys::KeyType kw2 = Keys::KeyType::INVALID;
    Keys::KeyType kw3 = Keys::KeyType::INVALID;

    kw1 = Keys::isValidKeyword(words[0]);
    if (words.size() > 1) kw2 = Keys::isValidKeyword(words[1]);
    if (words.size() > 2) kw3 = Keys::isValidKeyword(words[2]);

    //Valid first keywords are all 3 types, check it exists at all
    if (!(bool)kw1)
    {
        printf("Your first argument was invalid. Try again.\n");
        return false;
    }
    
    //Check what the first keyword is, this decides all following flow
    switch (kw1)
    {
        //Only one case here, it must be find the best seat I want
        case(Keys::KeyType::SEAT):
        {
            seatToReserve = getBestSeat(person->GetCredits(), Keys::Seat.at(words[0]));
            break;
        }
        //Two cases here, could be type alone or type with seat preference
        case(Keys::KeyType::CAR):
        {
            if (words.size() == 2 && kw2 == Keys::KeyType::SEAT)
            {
                seatToReserve = getBestSeat(person->GetCredits(), Keys::Seat.at(words[1]), Keys::Car.at(words[0]));
                break;
            }
            if(Keys::Car.at(words[0]) == CarType::PICKUP)
            {
                seatToReserve = getBestSeat(person->GetCredits(), SeatType::FRONT, CarType::PICKUP);
                break;
            }

            CLEAR_SCR();
            m_Fleet.printReservationVisual(Keys::Car.at(words[0]));
            printf("\n\nPlease select a type of seat;\n\n");
            printf("Seat type: front, back, side, middle. Only sedans have a middle seat. \n");
            printf("Enter no commas and seperate all words with spaces!!\nFormat should be the following\n");
            printf("   <Seat>\n\n > ");

            std::vector<std::string> seatSelWords = *WordsFromInput();
            if (seatSelWords.size() > 1)
            {
                printf("Incorrect amount of arguments. Please try again.\n");
                return false;
            }

            if (Keys::isValidKeyword(seatSelWords[0]) != Keys::KeyType::SEAT)
            {
                printf("Your second argument was not a valid seat type!\n");
                return false;
            }

            seatToReserve = getBestSeat(person->GetCredits(), Keys::Seat.at(seatSelWords[0]), Keys::Car.at(words[0]));
            break;
        }

        //Now for the long one
        case(Keys::KeyType::COLOR):
        {
            bool validSize = words.size() == 3;
            bool validArgTypes = kw2 == Keys::KeyType::CAR && kw3 == Keys::KeyType::SEAT;

            if ((uint8_t)Keys::Seat.at(words[2]) > person->GetCredits())
            {
                printf("Not enough credits for this type of seat!\n");
                return false;
            }

            if (!validSize || !validArgTypes)
            {
                printf("Your second or third argument was invalid. Try again.\n");
                return false;
            }

            seatToReserve = getBestSeat(person->GetCredits(), Keys::Seat.at(words[2]), Keys::Car.at(words[1]), Keys::Color.at(words[0]));
            break;
        }
        default:
            break;
    }

    //All specific errors are handled in the getBestSeat
    if (seatToReserve == nullptr)
    {
        return false;
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

Seat* UI::getBestSeat(uint32_t credits, SeatType seatIN, CarType carIN, CarColor colorIN)
{
    std::vector<Car*> possibleCars = m_Fleet.getCars(carIN);
            
    Car* carRequested = nullptr;
    for (Car* car : possibleCars)
    {
        if (car->getColor() == colorIN)
        {
            carRequested = car;
        }
    }

    if (carRequested == nullptr)
    {
        printf("There is no car of this type in this color. Try again.\n");
        return nullptr;
    }

    std::vector<Seat*> possibleSeats = carRequested->getSeats();

    if (seatIN == SeatType::BACK && carIN == CarType::SEDAN)
    {
        Seat* bestFound = nullptr; SeatType bestsType = SeatType::DRIVER;
        std::reverse(possibleSeats.begin(), possibleSeats.end());    
        int unaffordable = true;
        for (Seat* seat : possibleSeats)
        {
            if (seat->taken) 
            {
                continue;
            }
            if (seat->cost < credits)
            {
                continue;
            }

            if ((uint8_t)seat->type >= (uint8_t)bestsType)
            {
                //Change best found open seat if better is found
                unaffordable = false;
                bestFound = seat;
                bestsType = seat->type;
            }
        }

        if (unaffordable)
        {
            printf("You cannot afford this seat!\n");
            return nullptr;
        }

        return bestFound;
    }

    if (credits < (uint8_t)seatIN)
    {

    }

    for (Seat* seat : possibleSeats)
    {
        if (seat->taken || seat->type != seatIN)
        {
            continue;
        }

        if (seat->type == seatIN)
        {
            return seat;
        }
    }

    //Complete fail returns nullptr
    printf("All seats of the type you requested are taken. Please choose another.");
    return nullptr;
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
        int unaffordable = true;
        for (Seat* seat : lookingSeats)
        {
            if (seat->taken) 
            {
                continue;
            }
            if (seat->cost > credits)
            {
                continue;
            }

            if ((uint32_t)seat->type >= (uint32_t)bestsType && (uint32_t)seat->type <= (uint32_t)seatIN)
            {
                //Change best found open seat if better is found
                unaffordable = false;
                bestFound = seat;
                bestsType = seat->type;
            }
        }

        if (unaffordable)
        {
            printf("You cannot afford this seat!\n");
            return nullptr;
        }

        return bestFound;
    }
    
    if (credits < (uint8_t)seatIN)
    {
        printf("You do not have enough credits for this seat!\n");
        return nullptr;
    }

    for (Seat* seat : lookingSeats)
    {
        if (seat->type != seatIN || seat->taken)
        {
            continue;
        }
        
        return seat;
    }

    //Complete fail returns nullptr
    printf("All seats of the type you requested are taken. Please choose another.");
    return nullptr;
}

int UI::GetPersonFromName(std::string& name)
{   
    //to lower input
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return std::tolower(c); });


    for (int i = 0; i < m_People.size(); i++)
    {
        std::string nameV = m_People[i]->GetName();
        std::transform(nameV.begin(), nameV.end(), nameV.begin(), [](unsigned char c){ return std::tolower(c); });

        if (nameV == name)
        {
            return i;
        }
    }

    return -1;
}


bool UI::Destroy(uint32_t reservationNumber)
{
    //Reservation number shoudl never enter this function if it is out of bounds!!!
    Seat* seat = m_PassengerSeats[reservationNumber - 1]; 
    if (!seat->taken)
    {
        printf("Reservation %d does not exist!\n", reservationNumber);
        return false;
    }

    seat->taken = false;
    seat->personInSeat = new Person();
    
    return true;
}

// void UI::DisplayVisual()
// {

// }
