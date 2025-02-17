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
