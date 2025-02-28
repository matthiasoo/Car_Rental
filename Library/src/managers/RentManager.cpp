#include "RentManager.h"

#include <Client.h>
#include <Vehicle.h>

RentManager::RentManager() {
    this->currentRents = std::make_shared<RentRepository>();
    this->archiveRents = std::make_shared<RentRepository>();
}

RentManager::~RentManager() {}

std::vector<RentPtr> RentManager::getAllClientRents(ClientPtr client) {
    if (client != nullptr) {
        return this->currentRents->findBy([client](RentPtr rent) {
            return rent->getClient() == client;
        });
    }
}

RentPtr RentManager::getVehicleRent(VehiclePtr vehicle) {
    if (vehicle != nullptr) {
        return this->currentRents->findBy([vehicle](RentPtr rent) {
            return rent->getVehicle() == vehicle;
        }).front();
    } else {
        return nullptr;
    }
}

std::vector<RentPtr> RentManager::findRents(RentPredicate predicate) {
    return this->currentRents->findBy(predicate);
}

std::vector<RentPtr> RentManager::findAllRents() {
    return this->currentRents->findAll();
}

double RentManager::checkClientRentBalance(ClientPtr client) {
    double balance = 0;
    if (client != nullptr) {
        this->archiveRents->findBy([client, &balance](RentPtr rent) {
            balance += rent->getRentCost();
            return rent->getClient() == client;
        });
    }
    return balance;
}

RentPtr RentManager::rentVehicle(const int &id, ClientPtr client, VehiclePtr vehicle, pt::ptime &beginTime) {
    if (client != nullptr && vehicle != nullptr) {
        if (client->isArchive() == false && vehicle->isArchive() == false) {
            if (this->getAllClientRents(client).size() < client->getMaxVehicles()) {
                if (this->getVehicleRent(vehicle) == nullptr) {
                    RentPtr newRent = std::make_shared<Rent>(id, client, vehicle, beginTime);
                    this->currentRents->add(newRent);
                    return newRent;
                }
            }
        }
    } else {
        return nullptr;
    }
}

void RentManager::returnVehicle(VehiclePtr vehicle) {
    if (vehicle != nullptr) {
        if (this->getVehicleRent(vehicle) != nullptr) {
            RentPtr removal = this->getVehicleRent(vehicle);
            // removal->endRent(); endTime ???
            this->currentRents->remove(removal);
            this->archiveRents->add(removal);
        }
    }
}
