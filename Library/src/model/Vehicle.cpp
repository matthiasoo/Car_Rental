#include "Vehicle.h"
#include "InvalidValueException.h"

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

const double Vehicle::getActualRentalPrice() const {
    return this->getBasePrice();
}

const bool Vehicle::isArchive() const {
    return this->archive;
}

// void Vehicle::setPlateNumber(const std::string &plateNumber) {
//     if (plateNumber.empty()) {
//         throw InvalidTextException("Plate number is empty");
//     }
//     this->plateNumber = plateNumber;
// }

// void Vehicle::setBasePrice(const int &basePrice) {
//     if (basePrice < 0) {
//         throw InvalidValueException("Base price must be greater tha zero");
//     }
//     this->basePrice = basePrice;
// }

void Vehicle::setArchive() {
    this->archive = true;
}
