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

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 100);

bool isLoggedIn = false;
bool isAdmin = true;

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
    std::cout << "\nHello (name, surname)\n\n";
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
    std::cout << "2. Register new vehicle\n";
    std::cout << "3. Unregister vehicle\n";
    std::cout << "4. View all rents\n";
    std::cout << "5. Log out\n";
    std::cout << "6. Clear\n";
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
            addNewVehicle();
            break;
        case 3 :
            removeVehicle();
            break;
        case 4 :
            listAllRents();
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
#pragma endregion Handling

#pragma region ClientOptions
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
        std::cout << MAGENTA << "\nYour current rents:\n\n" << RESET;
        for (RentPtr rent : rentManager->getAllClientRents(client)) {
            std::cout << rent->getRentInfo() << "\n\n";
        }
        std::cout << MAGENTA << "Your archive rents:\n\n" << RESET;
        for (RentPtr rent : rentManager->getClientArchiveRents(client)) {
            std::cout << rent->getRentInfo() << "\n";
        }
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
    } catch (const ClientException &e) {
        std::cout << RED << "\n" << e.what() << RESET << "\n";
    }
}

void Menu::signUp() {
    std::cout << CYAN << "'Sign up' feature in development...\n" << RESET;
}

void Menu::logIn() {
    isLoggedIn = true;
    std::cout << CYAN << "'Log in' feature in development...\n" << RESET;
}

void Menu::logOut() {
    isLoggedIn = false;
    std::cout << CYAN << "'Log out' feature in development...\n" << RESET;
}
#pragma endregion ClientOptions

#pragma region RentOptions
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
        pt::ptime begin = pt::ptime(gr::date(2025, 5, 20), pt::hours(23) + pt::minutes(32));
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
        VehiclePtr vehicle = vehicleManager->getVehicle(plateNumber);
        this->rentManager->returnVehicle(client, vehicle);
        std::cout << GREEN << "\nYour rental ended successfully\n" << RESET;
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

void Menu::listAllRents() {
    std::cout << MAGENTA << "\nCurrent rents:\n\n" << RESET;
    std::cout << rentManager->listAllCurrentRents();
    std::cout << MAGENTA << "Archive rents:\n\n" << RESET;
    std::cout << rentManager->listAllArchiveRents();
}
#pragma endregion RentOptions

#pragma region VehicleOptions
void Menu::listVehicles() {
    std::cout << CYAN << "'List vehicles' feature in development...\n" << RESET;
}

void Menu::listAllVehicles() {
    std::cout << MAGENTA << "\nAll vehicles:\n\n" << RESET;
    std::cout << vehicleManager->listAllVehicles();
}

void Menu::addNewVehicle() {
    std::cout << CYAN << "'Add new vehicle' feature in development...\n" << RESET;
}

void Menu::removeVehicle() {
    std::cout << CYAN << "'Remove vehicle' feature in development...\n" << RESET;
}
#pragma endregion VehicleOptions
