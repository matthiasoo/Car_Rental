#ifndef RENT_H
#define RENT_H

#include <string>

class Client;
class Vehicle;

class Rent {
private:
    int id; // maybe unsigned
    Client  *client;
    Vehicle *vehicle;

public:
    Rent(const int &id, Client *client, Vehicle *vehicle);
    ~Rent();

    // getters
    std::string getRentInfo();
    const int &getId() const;
    const Client *getClient() const;
    const Vehicle *getVehicle() const;
};



#endif //RENT_H
