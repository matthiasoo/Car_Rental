#include "Bicycle.h"

Bicycle::Bicycle(const std::string &plateNumber, const int &basePrice) :
    Vehicle(plateNumber, basePrice) {}

Bicycle::~Bicycle() {}

const double Bicycle::getActualRentalPrice() const {
    return Vehicle::getActualRentalPrice();
}

std::string Bicycle::getVehicleInfo() const {
    return "Bicycle\n" + Vehicle::getVehicleInfo();
}
