#include "ClientType.h"

ClientType::ClientType() {}

ClientType::~ClientType() {}


Default::Default() {}

Default::~Default() {}

int Default::getMaxVehicles() {
    return 1;
}

double Default::applyDiscount(double price) {
    return 0;
}

std::string Default::getTypeInfo() {
    return "Default";
}

Bronze::Bronze() {}

Bronze::~Bronze() {}

int Bronze::getMaxVehicles() {
    return 2;
}

double Bronze::applyDiscount(double price) {
    return 3;
}

std::string Bronze::getTypeInfo() {
    return "Bronze";
}

Silver::Silver() {}

Silver::~Silver() {}

int Silver::getMaxVehicles() {
    return 3;
}

double Silver::applyDiscount(double price) {
    return 6;
}

std::string Silver::getTypeInfo() {
    return "Silver";
}

Gold::Gold() {}

Gold::~Gold() {}

int Gold::getMaxVehicles() {
    return 4;
}

double Gold::applyDiscount(double price) {
    return 0.05 * price;
}

std::string Gold::getTypeInfo() {
    return "Gold";
}

Platinum::Platinum() {}

Platinum::~Platinum() {}

int Platinum::getMaxVehicles() {
    return 5;
}

double Platinum::applyDiscount(double price) {
    return 0.1 * price;
}

std::string Platinum::getTypeInfo() {
    return "Platinum";
}

Diamond::Diamond() {}

Diamond::~Diamond() {}

int Diamond::getMaxVehicles() {
    return 10;
}

double Diamond::applyDiscount(double price) {
    double discount;
    if (price > 0 && price <= 125) {
        discount = 0.1 * price;
    } else if (price > 125 && price <= 250) {
        discount = 0.2 * price;
    } else if (price > 250 && price <= 500) {
        discount = 0.3 * price;
    } else {
        discount = 0.4 * price;
    }

    return discount;
}

std::string Diamond::getTypeInfo() {
    return "Diamond";
}
