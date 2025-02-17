#include "Client.h"
#include "Address.h"
#include "Rent.h"

// Client::Client() {
//     std::cout << "Constructor" << std::endl;
// }

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address) :
    firstName(firstName),
    lastName(lastName),
    personalID(personalID),
    address(address) {
    this->currentRents.clear();
}

Client::~Client() {}

std::string Client::getClientInfo() const {
    return "CLIENT: " + this->getFirstName() + " " + this->getLastName() + " " + this->getPersonalID()
        + "\n" + this->getAddress()->getAddressInfo();
}

std::string Client::getFullClientInfo() const {
    std::string fullInfo = this->getClientInfo() + "\nCURRENT RENTS:";
    for (int i = 0; i < currentRents.size(); i++) {
        fullInfo += "\n" + this->getCurrentRents()[i]->getRentInfo();
    }
    return fullInfo;
}

const std::string & Client::getFirstName() const {
    return this->firstName;
}

const std::string & Client::getLastName() const {
    return this->lastName;
}

const std::string & Client::getPersonalID() const {
    return this->personalID;
}

const AddressPtr Client::getAddress() const {
    return this->address;
}

const std::vector<Rent*> &Client::getCurrentRents() const {
    return this->currentRents;
}

void Client::setFirstName(const std::string &firstName) {
    if (!firstName.empty()) {
        this->firstName = firstName;
    }
}

void Client::setLastName(const std::string &lastName) {
    if (!lastName.empty()) {
        this->lastName = lastName;
    }
}

void Client::setAddress(AddressPtr address) {
    if (address != nullptr) {
        this->address = address;
    }
}

void Client::addRent(Rent *rent) {
    if (rent != nullptr) {
        this->currentRents.push_back(rent);
    }
}

void Client::removeRent(Rent *rent) {
    if (rent != nullptr) {
        for (int i = 0; i < this->currentRents.size(); i++) {
            if (this->currentRents[i] == rent) {
                this->currentRents.erase(this->currentRents.begin() + i);
            }
        }
    }
}