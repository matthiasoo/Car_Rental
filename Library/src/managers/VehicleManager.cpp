#include "VehicleManager.h"

#include <VehicleException.h>

VehicleManager::VehicleManager() {
    this->activeVehicles = std::make_shared<VehicleRepository>();
    this->archiveVehicles = std::make_shared<VehicleRepository>();
}

VehicleManager::~VehicleManager() {}

VehiclePtr VehicleManager::getVehicle(const std::string &plateNumber) {
    return this->activeVehicles->findByPlateNumber(plateNumber);
}

VehiclePtr VehicleManager::registerBicycle(const std::string &plateNumber, const int &basePrice) {
    if (this->getVehicle(plateNumber) != nullptr) {
        throw VehicleException("Vehicle with plate number: " + plateNumber + " already exists!");
    } else {
        VehiclePtr newBicycle = std::make_shared<Bicycle>(plateNumber, basePrice);
        this->activeVehicles->add(newBicycle);
        return newBicycle;
    }
}

VehiclePtr VehicleManager::registerMoped(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement) {
    if (this->getVehicle(plateNumber) != nullptr) {
        throw VehicleException("Vehicle with plate number: " + plateNumber + " already exists!");
    } else {
        VehiclePtr newMoped = std::make_shared<Moped>(plateNumber, basePrice, engineDisplacement);
        this->activeVehicles->add(newMoped);
        return newMoped;
    }
}

VehiclePtr VehicleManager::registerCar(const std::string &plateNumber, const int &basePrice, const int &engineDisplacement, const SegmentType &segment) {
    if (this->getVehicle(plateNumber) != nullptr) {
        throw VehicleException("Vehicle with plate number: " + plateNumber + " already exists!");
    } else {
        VehiclePtr newCar = std::make_shared<Car>(plateNumber, basePrice, engineDisplacement, segment);
        this->activeVehicles->add(newCar);
        return newCar;
    }
}

// TODO check if the vehicle is not currently rented
void VehicleManager::unregisterVehicle(const std::string &plateNumber) {
    if (!this->getVehicle(plateNumber)) throw VehicleException("Vehicle with plate number: " + plateNumber + " not found!");
    VehiclePtr vehicle = this->getVehicle(plateNumber);
    activeVehicles->remove(vehicle);
    vehicle->setArchive();
    archiveVehicles->add(vehicle);
}

std::vector<VehiclePtr> VehicleManager::findVehicles(VehiclePredicate predicate) {
    return this->activeVehicles->findBy([predicate](VehiclePtr vehicle) {
        return !vehicle->isRented() && predicate(vehicle);
    });
}

std::vector<VehiclePtr> VehicleManager::findArchiveVehicles() {
    return this->archiveVehicles->findAll();
}

std::vector<VehiclePtr> VehicleManager::findActiveVehicles() {
    return this->activeVehicles->findAll();
}

std::string VehicleManager::listVehicles(bool archive) {
    if (archive) return archiveVehicles->report();
    return activeVehicles->report();
}