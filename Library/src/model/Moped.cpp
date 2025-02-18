#include "Moped.h"

Moped::Moped(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement) :
    MotorVehicle(plateNumber, basePrice, engineDisplacement) {}

Moped::~Moped() {
}

const double Moped::getActualRentalPrice() const {
    return MotorVehicle::getActualRentalPrice();
}

std::string Moped::getVehicleInfo() const {
    return "Moped " + MotorVehicle::getVehicleInfo();
}
