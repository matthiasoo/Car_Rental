#include "RentRepository.h"
#include "colors.h"

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
        info += std::string(MAGENTA) + std::to_string(i+1) + ".\n" + std::string(RESET)
        + this->rentRepository[i]->getRentInfo() + "\n\n";
    }

    return info;
}

int RentRepository::size() {
    return this->rentRepository.size();
}

std::vector<RentPtr> RentRepository::findBy(RentPredicate predicate) const {
    std::vector<RentPtr> found;
    for (int i = 0; i < rentRepository.size(); i++) {
        RentPtr rent = get(i);
        if (rent != nullptr && predicate(rent)) {
            found.push_back(rent);
        }
    }
    return found;
}

std::vector<RentPtr> RentRepository::findAll() const {
    return findBy([](RentPtr) { return true; });
}
