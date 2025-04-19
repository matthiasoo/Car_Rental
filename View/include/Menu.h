#ifndef MENU_H
#define MENU_H
#include "typedefs.h"

class Menu {
public:
    void run();

private:
    ClientManagerPtr clientManager;

    void showMainOptions();
    void handleChoice(int choice);
    void initRepos();

    void addClient();
    void checkClient();
};



#endif //MENU_H
