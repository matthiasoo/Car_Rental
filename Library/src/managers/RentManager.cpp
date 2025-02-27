#include "RentManager.h"

RentManager::RentManager() {
    this->currentRents = std::make_shared<RentRepository>();
    this->archiveRents = std::make_shared<RentRepository>();
}

RentManager::~RentManager() {}

std::vector<RentPtr> RentManager::getAllClientRents(ClientPtr client) {
}

RentPtr RentManager::getVehicleRent(VehiclePtr vehicle) {
}

std::vector<RentPtr> RentManager::findRents(RentPtr predicate) {
}

std::vector<RentPtr> RentManager::findAllRents() {
}

double RentManager::checkClientRentBalance(ClientPtr client) {
}
