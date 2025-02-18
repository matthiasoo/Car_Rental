#include "Vehicle.h"

Vehicle::Vehicle(const std::string &plateNumber, const int &basePrice) :
    plateNumber(plateNumber),
    basePrice(basePrice) {}

Vehicle::~Vehicle() {}

std::string Vehicle::getVehicleInfo() const {
    return this->plateNumber + " " + std::to_string(this->basePrice);
}

const std::string & Vehicle::getPlateNumber() const {
    return this->plateNumber;
}

const int & Vehicle::getBasePrice() const {
    return this->basePrice;
}

const bool & Vehicle::getRentState() const {
    return this->rentState;
}

const double Vehicle::getActualRentalPrice() const {
    return this->getBasePrice();
}

void Vehicle::setPlateNumber(const std::string &plateNumber) {
    if (!plateNumber.empty()) {
        this->plateNumber = plateNumber;
    }
}

void Vehicle::setBasePrice(const int &basePrice) {
    if (basePrice >= 0) {
        this->basePrice = basePrice;
    }
}

void Vehicle::setRentState(const bool &rentState) {
    this->rentState = rentState;
}
