#include "Client.h"
#include "Address.h"
#include <iostream>

// Client::Client() {
//     std::cout << "Constructor" << std::endl;
// }

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, Address *address) :
    firstName(firstName),
    lastName(lastName),
    personalID(personalID),
    address(address) {}

Client::~Client() {}

std::string Client::getClientInfo() const {
    return this->getFirstName() + " " + this->getLastName() + " " + this->getPersonalID() + ", " + this->getAddress()->getAddressInfo();
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

const Address* Client::getAddress() const {
    return this->address;
}

void Client::setFirstName(const std::string &firstName) {
    if (firstName != "") {
        this->firstName = firstName;
    }
}

void Client::setLastName(const std::string &lastName) {
    if (lastName != "") {
        this->lastName = lastName;
    }
}

void Client::setAddress(Address *address) {
    if (address != nullptr) {
        this->address = address;
    }
}
