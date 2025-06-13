#ifndef MENU_H
#define MENU_H
#include "typedefs.h"

class Menu {
public:
    void run();

private:
    ClientManagerPtr clientManager;
    VehicleManagerPtr vehicleManager;
    RentManagerPtr rentManager;

    void showMainMenuNLI(); // not logged in
    void showMainMenuUser(); // user logged in
    void showMainMenuAdmin(); // admin logged in

    void handleMainMenuNLI(int choice);
    void handleMainMenuUser(int choice);
    void handleMainMenuAdmin(int choice);

    void initRepos();
    void initVehicles();
    void initClients();

    void checkClient();
    void listAllClients();
    void disableClient();
    void signUp();
    void logIn();
    void logOut();

    void rent();
    void endRent();
    void listAllRents();

    void listVehicles();
    void listAllVehicles();
    void addNewVehicle();
    void removeVehicle();
};



#endif //MENU_H
