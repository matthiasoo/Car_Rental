#include "Menu.h"
#include "ClientException.h"
#include "ClientManager.h"
#include "InvalidValueException.h"
#include "Address.h"
#include "typedefs.h"
#include <iostream>
#include <random>
#include "Vehicle.h"
#include "VehicleManager.h"
#include "RentManager.h"
#include "NullPointerException.h"
#include "VehicleException.h"
#include "RentException.h"
#include "colors.h"
#include <regex>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 100);

bool isLoggedIn = false;
bool isAdmin = false;
ClientPtr currentClient = nullptr;

void Menu::run() {
    int choice = 0;
    initRepos();
    initVehicles();
    initClients();
    system("cls");
    do {
        if (!isLoggedIn) {
            showMainMenuNLI();
            std::cout << "\n" << BBLACK << "Choose option: " << RESET;
            std::cin >> choice;
            handleMainMenuNLI(choice);
            std::cout << "\n";
        } else {
            if (!isAdmin) {
                showMainMenuUser();
                std::cout << "\n" << BBLACK << "Choose option: " << RESET;
                std::cin >> choice;
                handleMainMenuUser(choice);
                std::cout << "\n";
            } else {
                showMainMenuAdmin();
                std::cout << "\n" << BBLACK << "Choose option: " << RESET;
                std::cin >> choice;
                handleMainMenuAdmin(choice);
                std::cout << "\n";
            }
        }
    } while (choice != 777);
}

#pragma region ShowMenu
void Menu::showMainMenuNLI() {
    std::cout << YELLOW << "CAR RENTAL\n" << RESET;
    std::cout << BYELLOW << "1. Sign up\n";
    std::cout << "2. Log in\n";
    std::cout << "5. Clear\n";
    std::cout << "777. Quit\n" << RESET;
}

void Menu::showMainMenuUser() {
    std::cout << YELLOW << "CAR RENTAL\n" << RESET;
    std::cout << "\nHello " << currentClient->getFirstName() << "\n\n";
    std::cout << BYELLOW << "1. Check out your profile\n";
    std::cout << "2. Check out our vehicles\n";
    std::cout << "3. Rent vehicle\n";
    std::cout << "4. Return vehicle\n";
    std::cout << "5. Log out\n";
    std::cout << "6. Clear\n";
    std::cout << "777. Quit\n" << RESET;
}

void Menu::showMainMenuAdmin() {
    std::cout << YELLOW << "CAR RENTAL\n" << RESET;
    std::cout << "\nHello Admin\n\n";
    std::cout << "1. View all vehicles\n";
    std::cout << "2. View all clients\n";
    std::cout << "3. Register new vehicle\n";
    std::cout << "4. Unregister vehicle\n";
    std::cout << "5. View all rents\n";
    std::cout << "6. Log out\n";
    std::cout << "7. Clear\n";
    std::cout << "777. Quit\n" << RESET;
}
#pragma endregion ShowMenu

#pragma region Init
void Menu::initRepos() {
    clientManager = std::make_shared<ClientManager>();
    vehicleManager = std::make_shared<VehicleManager>();
    rentManager = std::make_shared<RentManager>();
}

void Menu::initVehicles() {
    vehicleManager->registerBicycle("B401", 20);
    vehicleManager->registerMoped("M824", 50, 125);
    vehicleManager->registerCar("C681", 200, 1600, C);
}

void Menu::initClients() {
    AddressPtr address = std::make_shared<Address>("LA", "Sunny", "7");
    ClientTypePtr type = std::make_shared<Default>();
    ClientPtr client = clientManager->registerClient("Brad", "Pitt", "123", address, type);
}
#pragma endregion Init

#pragma region Handling
void Menu::handleMainMenuNLI(int choice) {
    switch (choice) {
        case 1 :
            signUp();
            break;
        case 2 :
            logIn();
            break;
        case 3 :
            system("cls");
            break;
        case 777 :
            std::cout << CYAN << "\nClosing app\n" << RESET;
            break;
        default :
            std::cout << RED << "\nInvalid choice. Try again.\n" << RESET;
            break;
    }
}

void Menu::handleMainMenuUser(int choice) {
    switch (choice) {
        case 1 :
            checkClient();
            break;
        case 2 :
            listVehicles();
            break;
        case 3 :
            rent();
            break;
        case 4 :
            endRent();
            break;
        case 5 :
            logOut();
            break;
        case 6 :
            system("cls");
            break;
        case 777 :
            std::cout << CYAN << "\nClosing app\n" << RESET;
            break;
        default :
            std::cout << RED << "\nInvalid choice. Try again.\n" << RESET;
            break;
    }
}

void Menu::handleMainMenuAdmin(int choice) {
    switch (choice) {
        case 1 :
            listAllVehicles();
            break;
        case 2 :
            listAllClients();
            break;
        case 3 :
            addNewVehicle();
            break;
        case 4 :
            removeVehicle();
            break;
        case 5 :
            listAllRents();
            break;
        case 6 :
            logOut();
            break;
        case 7 :
            system("cls");
            break;
        case 777 :
            std::cout << CYAN << "\nClosing app\n" << RESET;
            break;
        default :
            std::cout << RED << "\nInvalid choice. Try again.\n" << RESET;
            break;
    }
}
#pragma endregion Handling

#pragma region ClientOptions

void Menu::checkClient() {
    std::cout << MAGENTA << "\nYour profile:\n\n" << RESET << currentClient->getClientInfo() << "\n";
    std::cout << MAGENTA << "\nYour current rents:\n\n" << RESET;
    for (RentPtr rent : rentManager->getAllClientRents(currentClient)) {
        std::cout << rent->getRentInfo() << "\n\n";
    }
    std::cout << MAGENTA << "Your archive rents:\n\n" << RESET;
    for (RentPtr rent : rentManager->getClientArchiveRents(currentClient)) {
        std::cout << rent->getRentInfo() << "\n";
    }
}

void Menu::disableClient() {
    clientManager->unregisterClient(currentClient->getPersonalID());
    std::cout << GREEN << "\nAccount disabled successfully!\n" << RESET;
}

void Menu::signUp() {
    std::string firstName;
    std::string lastName;
    std::string personalID;
    std::string city;
    std::string street;
    std::string number;

    try {
        std::cout << BBLACK << "\nEnter your name: " << RESET;
        std::cin >> firstName;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << BBLACK << "Enter your surname: " << RESET;
        std::getline(std::cin, lastName);
        std::cout << BBLACK << "Enter your ID: " << RESET;
        std::cin >> personalID;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << BBLACK << "Enter your city: " << RESET;
        std::getline(std::cin, city);
        std::cout << BBLACK << "Enter your street: " << RESET;
        std::getline(std::cin, street);
        std::cout << BBLACK << "Enter your street number: " << RESET;
        std::cin >> number;
        AddressPtr address = std::make_shared<Address>(city, street, number);
        ClientTypePtr type = std::make_shared<Default>();
        ClientPtr client = clientManager->registerClient(firstName, lastName, personalID, address, type);
        std::cout << GREEN << "\nSigned up successfully!\n" << RESET;

        isLoggedIn = true;
        currentClient = client;
    } catch (const InvalidValueException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const NullPointerException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const ClientException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::logIn() {
    std::string login;

    std::cout << BBLACK << "Enter your ID: " << RESET;
    std::cin >> login;

    if (login == "admin") {
        isLoggedIn = true;
        isAdmin = true;
        std::cout << GREEN << "Logged in succesfully!" << RESET << "\n";
        return;
    }

    try {
        currentClient = clientManager->getClient(login);
        isLoggedIn = true;
        std::cout << GREEN << "Logged in succesfully!" << RESET << "\n";
    } catch (const ClientException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::logOut() {
    currentClient = nullptr;
    isLoggedIn = false;
    isAdmin = false;

    std::cout << GREEN << "Logged out succesfully!" << RESET << "\n";
}

void Menu::listAllClients() {
    std::cout << MAGENTA << "\nAll clients:\n\n" << RESET;
    std::cout << clientManager->listAllClients();
}
#pragma endregion ClientOptions

#pragma region RentOptions
void Menu::rent() {
    std::string plateNumber;
    std::string time;
    std::regex datetimeRegex(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$)");

    try {
        std::cout << BBLACK << "\nEnter plate number of vehicle you want to rent: " << RESET;
        std::cin >> plateNumber;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        VehiclePtr vehicle = vehicleManager->getVehicle(plateNumber);
        std::cout << BBLACK << "\nEnter the start time od your rent in the following format: YYYY-MM-DD HH:MM : " << RESET;
        std::getline(std::cin, time);

        while (!std::regex_match(time, datetimeRegex)) {
            std::cout << RED << "\nInvalid format. " << BBLACK << "Please use format YYYY-MM-DD HH:MM: ";
            std::getline(std::cin, time);
        }

        pt::ptime begin = pt::time_from_string(time);
        rentManager->rentVehicle(dist(gen), currentClient, vehicle, begin);
        std::cout << GREEN << "\nYour rental will start " + to_simple_string(begin) + "\n" << RESET;
    } catch (const ClientException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const VehicleException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const NullPointerException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const RentException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::endRent() {
    std::string personalID;
    std::string plateNumber;

    try {
        std::cout << BBLACK << "\nEnter plate number of vehicle you want to return: " << RESET;
        std::cin >> plateNumber;
        VehiclePtr vehicle = vehicleManager->getVehicle(plateNumber);
        this->rentManager->returnVehicle(currentClient, vehicle);
        std::cout << GREEN << "\nYour rental ended successfully\n" << RESET;
    } catch (const VehicleException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const NullPointerException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const RentException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::listAllRents() {
    std::cout << MAGENTA << "\nCurrent rents:\n\n" << RESET;
    std::cout << rentManager->listRents(false);
    std::cout << MAGENTA << "Archive rents:\n\n" << RESET;
    std::cout << rentManager->listRents(true);
}
#pragma endregion RentOptions

#pragma region VehicleOptions
void Menu::listVehicles() {
    std::cout << MAGENTA << "\nOur vehicles:\n\n" << RESET;
    std::cout << vehicleManager->listVehicles(false);
}

void Menu::listAllVehicles() {
    std::cout << MAGENTA << "\nActive vehicles:\n\n" << RESET;
    std::cout << vehicleManager->listVehicles(false);
    std::cout << MAGENTA << "\nArchive vehicles:\n\n" << RESET;
    std::cout << vehicleManager->listVehicles(true);
}

void Menu::addNewVehicle() {
    int choice, basePrice, engineDisplacement;
    std::string plateNumber;
    char seg;
    SegmentType segment;

    std::cout << YELLOW << "REGISTER:\n" << RESET;
    std::cout << "1. Bicycle\n";
    std::cout << "2. Moped\n";
    std::cout << "3. Car\n";
    std::cout << "4. Quit\n" << RESET;
    std::cout << "\n" << BBLACK << "Choose option: " << RESET;
    std::cin >> choice;

    switch (choice) {
        case 1 :
            try {
                std::cout << BBLACK << "\nEnter plate number: " << RESET;
                std::cin >> plateNumber;
                std::cout << BBLACK << "\nEnter base price: " << RESET;
                std::cin >> basePrice;
                vehicleManager->registerBicycle(plateNumber, basePrice);
                std::cout << GREEN << "Registered successfully!\n" << RESET;
            } catch (const VehicleException &e) {
                std::cout << RED << "\n" << e.what() << RESET << "\n";
            }
            break;
        case 2 :
            try {
                std::cout << BBLACK << "\nEnter plate number: " << RESET;
                std::cin >> plateNumber;
                std::cout << BBLACK << "\nEnter base price: " << RESET;
                std::cin >> basePrice;
                std::cout << BBLACK << "\nEnter engine displacement: " << RESET;
                std::cin >> engineDisplacement;
                vehicleManager->registerMoped(plateNumber, basePrice, engineDisplacement);
                std::cout << GREEN << "Registered successfully!\n" << RESET;
            } catch (const VehicleException &e) {
                std::cout << RED << "\n" << e.what() << RESET << "\n";
            }
            break;
        case 3 :
            try {
                std::cout << BBLACK << "\nEnter plate number: " << RESET;
                std::cin >> plateNumber;
                std::cout << BBLACK << "\nEnter base price: " << RESET;
                std::cin >> basePrice;
                std::cout << BBLACK << "\nEnter engine displacement: " << RESET;
                std::cin >> engineDisplacement;
                std::cout << BBLACK << "\nEnter segment (A, B, C, D, E): " << RESET;
                std::cin >> seg;
                switch (seg) {
                    case 'a':
                    case 'A':
                        segment = A;
                        break;
                    case 'b':
                    case 'B':
                        segment = B;
                        break;
                    case 'c':
                    case 'C':
                        segment = C;
                        break;
                    case 'd':
                    case 'D':
                        segment = D;
                        break;
                    case 'e':
                    case 'E':
                        segment = E;
                        break;
                    default:
                        std::cout << RED << "Wrong segment type!\n" << RESET;
                        return;
                }
                vehicleManager->registerCar(plateNumber, basePrice, engineDisplacement, segment);
                std::cout << GREEN << "Registered successfully!\n" << RESET;
            } catch (const VehicleException &e) {
                std::cout << RED << "\n" << e.what() << RESET << "\n";
            }
            break;
        case 4 :
            break;
        default :
            std::cout << RED << "\nInvalid choice!\n" << RESET;
            break;
    }
}

void Menu::removeVehicle() {
    std::string plateNumber;

    try {
        std::cout << BBLACK << "\nEnter plate number: " << RESET;
        std::cin >> plateNumber;
        vehicleManager->unregisterVehicle(plateNumber);
        std::cout << GREEN << "Unregistered successfully!\n" << RESET;
    } catch (const VehicleException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}
#pragma endregion VehicleOptions
