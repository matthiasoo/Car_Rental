#include "Rent.h"
#include "Client.h"
#include "Vehicle.h"

Rent::Rent(const int &id, ClientPtr client, VehiclePtr vehicle, const pt::ptime &beginTime) :
    id(id),
    client(client),
    vehicle(vehicle),
    beginTime(beginTime) {
    this->client->addRent(this);
    this->vehicle->setRentState(true);
    if (this->beginTime == pt::not_a_date_time) {
        this->beginTime = pt::second_clock::local_time();
    };
}

Rent::~Rent() {}

std::string Rent::getRentInfo() const {
    return "ID: " + std::to_string(this->id) + "\n" + this->client->getClientInfo() + ", " + this->vehicle->getVehicleInfo()
    + "\nBEGIN TIME:" + to_simple_string(this->beginTime) + ", END TIME: " + to_simple_string(this->endTime);
}

const int & Rent::getId() const {
    return this->id;
}

const ClientPtr Rent::getClient() const {
    return this->client;
}

const VehiclePtr Rent::getVehicle() const {
    return this->vehicle;
}

const pt::ptime & Rent::getBeginTime() const {
    return this->beginTime;
}

const pt::ptime & Rent::getEndTime() const {
    return this->endTime;
}

int Rent::getRentDays() {
    if (!this->endTime.is_not_a_date_time()) {
        pt::time_period period(this->beginTime, this->endTime);

        if ((period.length().minutes() + period.length().hours() * 60) <= 1) {
            return 0;
        } else {
            return period.length().hours() / 24 + 1; // floor ?
        }
    } else {
        return 0; // if end time has not been set yet
    }
}

int Rent::getRentCost() {
    return this->rentCost;
}


void Rent::endRent(const pt::ptime &endTime) {
    if (this->endTime.is_not_a_date_time()) {
        if (endTime.is_not_a_date_time()) {
            this->endTime = pt::second_clock::local_time();
        } else {
            if (endTime <= this->beginTime) {
                this->endTime = this->beginTime;
            } else {
                this->endTime = endTime;
            }
        }
        this->rentCost = this->getRentDays() * this->vehicle->getBasePrice();
        this->vehicle->setRentState(false);
        this->client->removeRent(this);
    }
}