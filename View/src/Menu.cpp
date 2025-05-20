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

constexpr const char* RESET       = "\033[0m";

constexpr const char* BLACK       = "\033[0;30m";
constexpr const char* RED         = "\033[0;31m";
constexpr const char* GREEN       = "\033[0;32m";
constexpr const char* YELLOW      = "\033[0;33m";
constexpr const char* BLUE        = "\033[0;34m";
constexpr const char* MAGENTA     = "\033[0;35m";
constexpr const char* CYAN        = "\033[0;36m";
constexpr const char* WHITE       = "\033[0;37m";

constexpr const char* BBLACK      = "\033[1;30m";
constexpr const char* BRED        = "\033[1;31m";
constexpr const char* BGREEN      = "\033[1;32m";
constexpr const char* BYELLOW     = "\033[1;33m";
constexpr const char* BBLUE       = "\033[1;34m";
constexpr const char* BMAGENTA    = "\033[1;35m";
constexpr const char* BCYAN       = "\033[1;36m";
constexpr const char* BWHITE      = "\033[1;37m";

constexpr const char* BG_BLACK    = "\033[40m";
constexpr const char* BG_RED      = "\033[41m";
constexpr const char* BG_GREEN    = "\033[42m";
constexpr const char* BG_YELLOW   = "\033[43m";
constexpr const char* BG_BLUE     = "\033[44m";
constexpr const char* BG_MAGENTA  = "\033[45m";
constexpr const char* BG_CYAN     = "\033[46m";
constexpr const char* BG_WHITE    = "\033[47m";

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 100);

void Menu::run() {
    int choice = 0;
    initRepos();
    initVehicles();
    system("cls");
    do {
        showMainOptions();
        std::cout << "\n" << BBLACK << "Choose option: " << RESET;
        std::cin >> choice;
        handleChoice(choice);
        std::cout << "\n";
    } while (choice != 777);
}

void Menu::showMainOptions() {
    std::cout << YELLOW << "CAR RENTAL\n" << RESET;
    std::cout << BYELLOW << "1. Sign up\n";
    std::cout << "2. Your profile\n";
    std::cout << "3. Disable your account\n";
    std::cout << "4. Rent\n";
    std::cout << "5. End rent\n";
    std::cout << "6. Clear\n";
    std::cout << "777. Quit\n" << RESET;
}

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

void Menu::handleChoice(int choice) {
    switch (choice) {
        case 1 :
            addClient();
            break;
        case 2 :
            checkClient();
            break;
        case 3 :
            disableClient();
            break;
        case 4 :
            rent();
            break;
        case 5 :
            endRent();
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

void Menu::addClient() {
    std::string firstName;
    std::string lastName;
    std::string personalID;
    std::string city;
    std::string street;
    std::string number;

    std::cout << BBLACK << "\nEnter your name: " << RESET;
    std::cin >> firstName;
    std::cout << BBLACK << "Enter your surname: " << RESET;
    std::cin >> lastName;
    std::cout << BBLACK << "Enter your ID: " << RESET;
    std::cin >> personalID;
    std::cout << BBLACK << "Enter your city: " << RESET;
    std::cin >> city;
    std::cout << BBLACK << "Enter your street: " << RESET;
    std::cin >> street;
    std::cout << BBLACK << "Enter your street number: " << RESET;
    std::cin >> number;

    try {
        AddressPtr address = std::make_shared<Address>(city, street, number);
        ClientTypePtr type = std::make_shared<Default>();
        ClientPtr client = clientManager->registerClient(firstName, lastName, personalID, address, type);
        // AddressPtr address = std::make_shared<Address>("LA", "Sunny", "7");
        // ClientTypePtr type = std::make_shared<Default>();
        // ClientPtr client = clientManager->registerClient("Brad", "Pitt", "123", address, type);

        std::cout << GREEN << "\nSigned up successfully!\n" << RESET;
    } catch (const InvalidValueException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const NullPointerException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const ClientException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::checkClient() {
    std::string personalID;

    std::cout << BBLACK << "\nEnter your ID: " << RESET;
    std::cin >> personalID;
    try {
        ClientPtr client = clientManager->getClient(personalID);
        std::cout << MAGENTA << "\nYour profile:\n\n" << RESET << client->getClientInfo() << "\n";
    } catch (const ClientException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::disableClient() {
    std::string personalID;

    std::cout << BBLACK << "\nEnter your ID: " << RESET;
    std::cin >> personalID;
    try {
        clientManager->unregisterClient(personalID);
        std::cout << GREEN << "\nAccount disabled successfully!\n" << RESET;
    } catch (const ClientException &e)
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::rent() {
    std::string personalID;
    std::string plateNumber;

    std::cout << BBLACK << "\nEnter your ID: " << RESET;
    std::cin >> personalID;

    try {
        ClientPtr client = clientManager->getClient(personalID);
        std::cout << BBLACK << "\nEnter plate number of vehicle you want to rent: " << RESET;
        std::cin >> plateNumber;
        VehiclePtr vehicle = vehicleManager->getVehicle(plateNumber);
        pt::ptime begin = pt::ptime(gr::date(2025, 5, 1), pt::hours(19));
        rentManager->rentVehicle(dist(gen), client, vehicle, begin);
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
        std::cout << BBLACK << "\nEnter your ID: " << RESET;
        std::cin >> personalID;
        ClientPtr client = clientManager->getClient(personalID);
        std::cout << BBLACK << "\nEnter plate number of vehicle you want to return: " << RESET;
        std::cin >> plateNumber;
    } catch (const ClientException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const VehicleException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const NullPointerException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    } catch (const RentException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }

    std::cout << CYAN << "\nIn development ...\n" << RESET;
}
