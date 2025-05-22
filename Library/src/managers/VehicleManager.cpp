#include "VehicleManager.h"

#include <VehicleException.h>

VehicleManager::VehicleManager() {
    this->vehicleRepo = std::make_shared<VehicleRepository>();
}

VehicleManager::~VehicleManager() {}

VehiclePtr VehicleManager::getVehicle(const std::string &plateNumber) {
    return this->vehicleRepo->findByPlateNumber(plateNumber);
}

VehiclePtr VehicleManager::registerBicycle(const std::string &plateNumber, const int &basePrice) {
    if (this->getVehicle(plateNumber) != nullptr) {
        return this->getVehicle(plateNumber);
    } else {
        VehiclePtr newBicycle = std::make_shared<Bicycle>(plateNumber, basePrice);
        this->vehicleRepo->add(newBicycle);
        return newBicycle;
    }
}

VehiclePtr VehicleManager::registerMoped(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement) {
    if (this->getVehicle(plateNumber) != nullptr) {
        return this->getVehicle(plateNumber);
    } else {
        VehiclePtr newMoped = std::make_shared<Moped>(plateNumber, basePrice, engineDisplacement);
        this->vehicleRepo->add(newMoped);
        return newMoped;
    }
}

VehiclePtr VehicleManager::registerCar(const std::string &plateNumber, const int &basePrice, const int& engineDisplacement, const SegmentType &segment) {
    if (this->getVehicle(plateNumber) != nullptr) {
        return this->getVehicle(plateNumber);
    } else {
        VehiclePtr newCar = std::make_shared<Car>(plateNumber, basePrice, engineDisplacement, segment);
        this->vehicleRepo->add(newCar);
        return newCar;
    }
}

void VehicleManager::unregisterVehicle(const std::string &plateNumber) {
    if (!this->getVehicle(plateNumber)) throw VehicleException("Vehicle with plate number: " + plateNumber + " not found!");
    this->getVehicle(plateNumber)->setArchive();
}

std::vector<VehiclePtr> VehicleManager::findVehicles(VehiclePredicate predicate) {
    return this->vehicleRepo->findBy([predicate](VehiclePtr vehicle) {
        return !vehicle->isArchive() && predicate(vehicle);
    });
}

std::vector<VehiclePtr> VehicleManager::findAllVehicles() {
    return this->findVehicles([](VehiclePtr) { return true; } );
}

std::string VehicleManager::listAllVehicles() {
    return this->vehicleRepo->report();
}