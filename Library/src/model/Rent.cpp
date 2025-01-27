#include "../../include/model/Rent.h"

#include <Client.h>
#include <Vehicle.h>

Rent::Rent(const int &id, Client *client, Vehicle *vehicle) :
    id(id),
    client(client),
    vehicle(vehicle) {}

Rent::~Rent() {}

std::string Rent::getRentInfo() {
    return std::to_string(id) + ": " + this->getClient()->getClientInfo() + ", " + this->getVehicle()->getVehicleInfo();
}

const int & Rent::getId() const {
    return this->id;
}

const Client * Rent::getClient() const {
    return this->client;
}

const Vehicle * Rent::getVehicle() const {
    return this->vehicle;
}