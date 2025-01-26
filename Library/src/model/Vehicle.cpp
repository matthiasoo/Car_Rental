#include "Vehicle.h"

Vehicle::Vehicle(const std::string &plateNumber, const int &basePrice) :
    plateNumber(plateNumber),
    basePrice(basePrice) {}

Vehicle::~Vehicle() {}

std::string Vehicle::getVehicleInfo() {
    return this->getPlateNumber() + " " + std::to_string(this->getBasePrice());
}

const std::string & Vehicle::getPlateNumber() const {
    return this->plateNumber;
}

const int & Vehicle::getBasePrice() const {
    return this->basePrice;
}

void Vehicle::setPlateNumber(const std::string &plateNumber) {
    if (plateNumber != "") {
        this->plateNumber = plateNumber;
    }
}

void Vehicle::setBasePrice(const int &basePrice) {
    if (basePrice >= 0) {
        this->basePrice = basePrice;
    }
}
