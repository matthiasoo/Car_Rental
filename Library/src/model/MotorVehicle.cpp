#include <iostream>
#include "MotorVehicle.h"

MotorVehicle::MotorVehicle(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement) :
    Vehicle(plateNumber, basePrice),
    engineDisplacement(engineDisplacement) {}

MotorVehicle::~MotorVehicle() {
}

const double MotorVehicle::getActualRentalPrice() const {
    double multiplier;
    if (this->engineDisplacement < 1000) { // > 0 ???
        multiplier = 1.0;
    } else if (this->engineDisplacement >= 1000 && this->engineDisplacement < 2000) {
        multiplier = 1.0 + (this->engineDisplacement - 1000) / 2000.0;
    } else {
        multiplier = 1.5;
    }

    return Vehicle::getActualRentalPrice() * multiplier;
}

std::string MotorVehicle::getVehicleInfo() const {
    return Vehicle::getVehicleInfo() + " " + std::to_string(this->engineDisplacement);
}
