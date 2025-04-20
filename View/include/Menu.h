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

    void showMainOptions();
    void handleChoice(int choice);

    void initRepos();
    void initVehicles();

    void addClient();
    void checkClient();
    void disableClient();

    void rent();
    void endRent();
};



#endif //MENU_H
