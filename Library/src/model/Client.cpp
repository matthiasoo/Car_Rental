#include "Client.h"

#include <ClientType.h>

#include "Address.h"
#include "Rent.h"

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address, ClientTypePtr clientType) :
    firstName(firstName),
    lastName(lastName),
    personalID(personalID),
    address(address),
    clientType(clientType) {}

Client::~Client() {}

std::string Client::getClientInfo() const {
    return "CLIENT: " + this->firstName + " " + this->lastName + " " + this->personalID
        + "\n" + this->address->getAddressInfo()
        + "\nTYPE:" + this->clientType->getTypeInfo();
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

const int Client::getMaxVehicles() const {
    return this->clientType->getMaxVehicles();
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

void Client::setClientType(ClientTypePtr clientType) {
    if (clientType != nullptr) {
        this->clientType = clientType;
    }
}

const double Client::applyDiscount(double price) {
    return this->clientType->applyDiscount(price);
}