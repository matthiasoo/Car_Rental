#include <Client.h>
#include <Address.h>
#include <Vehicle.h>
#include <Rent.h>
#include <iostream>

int main() {

    Address *address1 = new Address("NYC", "Wall Street", "10");
    Client *client1 = new Client("Brad", "Pitt", "8899", address1);
    Vehicle *vehicle1 = new Vehicle("US0067", 200);
    Rent *rent1 = new Rent(1, client1, vehicle1);

    std::cout << rent1->getRentInfo() << std::endl;

    return 0;
}
