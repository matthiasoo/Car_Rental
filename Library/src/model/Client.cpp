#include "Client.h"
#include "InvalidTextException.h"
#include "NullPointerException.h"

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

const bool Client::isArchive() const {
    return this->archive;
}

void Client::setFirstName(const std::string &firstName) {
    if (firstName.empty()) {
        throw InvalidTextException("First name is empty.");
    }
    this->firstName = firstName;
}

void Client::setLastName(const std::string &lastName) {
    if (lastName.empty()) {
        throw InvalidTextException("Last name is empty.");
    }
    this->lastName = lastName;
}

void Client::setAddress(AddressPtr address) {
    if (address == nullptr) {
        throw NullPointerException
    }
    this->address = address;
}

void Client::setClientType(ClientTypePtr clientType) {
    if (clientType != nullptr) {
        this->clientType = clientType;
    }
}

void Client::setArchive() {
    this->archive = true;
}


const double Client::applyDiscount(double price) {
    return this->clientType->applyDiscount(price);
}