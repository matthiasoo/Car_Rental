#include "Car.h"

Car::Car(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement, const SegmentType &segment) :
    MotorVehicle(plateNumber, basePrice, engineDisplacement),
    segment(segment) {}

Car::~Car() {
}

const double Car::getActualRentalPrice() const {
    return MotorVehicle::getActualRentalPrice() * segment / 10.0;
}

std::string Car::getVehicleInfo() const {
    return "Car\n" + MotorVehicle::getVehicleInfo();
}
