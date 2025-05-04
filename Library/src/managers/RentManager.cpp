#include "RentManager.h"
#include "Client.h"
#include "NullPointerException.h"
#include "Vehicle.h"
#include "ClientException.h"
#include "VehicleException.h"
#include "RentException.h"

RentManager::RentManager() {
    this->currentRents = std::make_shared<RentRepository>();
    this->archiveRents = std::make_shared<RentRepository>();
}

RentManager::~RentManager() {}

std::vector<RentPtr> RentManager::getAllClientRents(ClientPtr client) {
    if (!client) throw NullPointerException("Client cannot be null!");
    return this->currentRents->findBy([client](RentPtr rent) {
            return rent->getClient() == client;
        });
}

RentPtr RentManager::getVehicleRent(VehiclePtr vehicle) {
    if (!vehicle) throw NullPointerException("Vehicle cannot be null!");
    std::vector<RentPtr> result =  this->currentRents->findBy([vehicle](RentPtr rent) {
            return rent->getVehicle() == vehicle;
        });
    if (result.size() == 0) return nullptr;
    return result.front();
}

std::vector<RentPtr> RentManager::findRents(RentPredicate predicate) {
    return this->currentRents->findBy(predicate);
}

std::vector<RentPtr> RentManager::findAllRents() {
    return this->currentRents->findAll();
}

double RentManager::checkClientRentBalance(ClientPtr client) {
    double balance = 0;

    if (!client) throw NullPointerException("Client cannot be null!");
    this->archiveRents->findBy([client, &balance](RentPtr rent) {
            balance += rent->getRentCost();
            return rent->getClient() == client;
        });
    return balance;
}

RentPtr RentManager::rentVehicle(const int &id, ClientPtr client, VehiclePtr vehicle, pt::ptime &beginTime) {
    if (!client) throw NullPointerException("Client cannot be null!");
    if (!vehicle) throw NullPointerException("Vehicle cannot be null!");
    if (client->isArchive()) throw ClientUnavailableException("Client account must be active!");
    if (vehicle->isArchive()) throw VehicleUnavailableException("Vehicle must be available!");
    if (this->getAllClientRents(client).size() >= client->getMaxVehicles())
        throw CannotRentException("Max number of rents achieved!");
    if (this->getVehicleRent(vehicle))
        throw VehicleAlreadyRentedException("Vehicle already rented!");

    RentPtr newRent = std::make_shared<Rent>(id, client, vehicle, beginTime);
    this->currentRents->add(newRent);
    return newRent;
}

void RentManager::returnVehicle(ClientPtr client, VehiclePtr vehicle) {
    if (!client) throw NullPointerException("Client cannot be null!");
    if (!vehicle) throw NullPointerException("Vehicle cannot be null!");
    if (!this->getVehicleRent(vehicle)) throw NullPointerException("Vehicle is not currently rented!");
    RentPtr removal = this->getVehicleRent(vehicle);
    if (removal->getClient() != client) throw NotYourVehicleException("This is not your vehicle!");
    removal->endRent(); // endTime ???
    changeClientType(removal->getClient());
    this->currentRents->remove(removal);
    this->archiveRents->add(removal);
}

RentRepositoryPtr RentManager::getArchiveRents() {
    return this->archiveRents;
}

void RentManager::changeClientType(ClientPtr client) {
    if (!client) throw NullPointerException("Client cannot be null!");
    double actualBalance = checkClientRentBalance(client);
    ClientTypePtr type = nullptr;
    if (actualBalance < 100) {
        type = std::make_shared<Default>();
    } else if (actualBalance >= 100 && actualBalance < 200) {
        type = std::make_shared<Bronze>();
    } else if (actualBalance >= 200 && actualBalance < 400) {
        type = std::make_shared<Silver>();
    } else if (actualBalance >= 400 && actualBalance < 800) {
        type = std::make_shared<Gold>();
    } else if (actualBalance >= 800 && actualBalance < 1600) {
        type = std::make_shared<Platinum>();
    } else if (actualBalance >= 1600) {
        type = std::make_shared<Diamond>();
    }

    client->setClientType(type);
}
