#include "Vehicle.h"
#include "InvalidValueException.h"
#include "colors.h"

Vehicle::Vehicle(const std::string &plateNumber, const int &basePrice) :
    plateNumber(plateNumber),
    basePrice(basePrice) {}

Vehicle::~Vehicle() {}

std::string Vehicle::getVehicleInfo() const {
    return "STATUS: " + (isArchive() ?
            std::string(BBLACK) + "ARCHIVE\n" + std::string(RESET) : (isRented() ?
                std::string(RED) + "UNAVAILABLE\n" + std::string(RESET) :
                std::string(GREEN) + "AVAILABLE\n" + std::string(RESET)))
    + plateNumber + " " + std::to_string(this->basePrice);
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

const bool Vehicle::isRented() const {
    return this->rented;
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

void Vehicle::setRented() {
    this->rented = !rented;
}