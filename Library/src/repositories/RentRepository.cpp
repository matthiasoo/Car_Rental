#include "RentRepository.h"

const RentPtr RentRepository::get(int index) const {
    if (index >= 0 && index < this->rentRepository.size()) {
        return this->rentRepository[index];
    } else {
        return nullptr;
    }
}

void RentRepository::add(RentPtr rent) {
    if (rent != nullptr) {
        this->rentRepository.push_back(rent);
    }
}

void RentRepository::remove(RentPtr rent) {
    if (rent != nullptr) {
        for (int i = 0; i < this->rentRepository.size(); i++) {
            if (this->rentRepository[i] == rent) {
                this->rentRepository.erase(this->rentRepository.begin() + i);
            }
        }
    }
}

std::string RentRepository::report() const {
    std::string info;
    for (int i = 0; i < this->rentRepository.size(); i++) {
        info += this->rentRepository[i]->getRentInfo() + "\n";
    }

    return info;
}

int RentRepository::size() {
    return this->rentRepository.size();
}
