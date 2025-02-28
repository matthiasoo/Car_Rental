#include "VehicleRepository.h"

const VehiclePtr VehicleRepository::get(int index) const {
    if (index >= 0 && index < this->vehicleRepository.size()) {
        return this->vehicleRepository[index];
    } else {
        return nullptr;
    }
}

void VehicleRepository::add(VehiclePtr vehicle) {
    if (vehicle != nullptr) {
        this->vehicleRepository.push_back(vehicle);
    }
}

void VehicleRepository::remove(VehiclePtr vehicle) {
    if (vehicle != nullptr) {
        for (int i = 0; i < this->vehicleRepository.size(); i++) {
            if (this->vehicleRepository[i] == vehicle) {
                this->vehicleRepository.erase(this->vehicleRepository.begin() + i);
            }
        }
    }
}

std::string VehicleRepository::report() const {
    std::string info;
    for (int i = 0; i < this->vehicleRepository.size(); i++) {
        info += this->vehicleRepository[i]->getVehicleInfo() + "\n";
    }

    return info;
}

int VehicleRepository::size() {
    return this->vehicleRepository.size();
}

std::vector<VehiclePtr> VehicleRepository::findBy(VehiclePredicate predicate) const {
    std::vector<VehiclePtr> found;
    for (int i = 0; i < vehicleRepository.size(); i++) {
        VehiclePtr vehicle = get(i);
        if (vehicle != nullptr && predicate(vehicle)) {
            found.push_back(vehicle);
        }
    }
    return found;
}

std::vector<VehiclePtr> VehicleRepository::findAll() const {
    return findBy([](VehiclePtr) { return true; });
}

VehiclePtr VehicleRepository::findByPlateNumber(const std::string& plateNumber) const {
    std::vector<VehiclePtr> result = findBy([plateNumber](VehiclePtr vehicle) {
        return vehicle->getPlateNumber() == plateNumber;
    });

    return result.empty() ? nullptr : result.front();
}
