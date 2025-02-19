#include "Client.h"
#include "Address.h"
#include "Rent.h"

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address) :
    firstName(firstName),
    lastName(lastName),
    personalID(personalID),
    address(address) {}

Client::~Client() {}

std::string Client::getClientInfo() const {
    return "CLIENT: " + this->firstName + " " + this->lastName + " " + this->personalID
        + "\n" + this->address->getAddressInfo();
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