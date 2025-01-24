#include "Client.h"
#include <iostream>

// Client::Client() {
//     std::cout << "Constructor" << std::endl;
// }

Client::Client(std::string firstName, std::string lastName, std::string personalID) :
    firstName(firstName),
    lastName(lastName),
    personalID(personalID) {}

Client::~Client() {}

std::string Client::getClientInfo() {
    return this->firstName + " " + this->lastName + " " + this->personalID;
}

std::string Client::getFirstName() {
    return this->firstName;
}

std::string Client::getLastName() {
    return this->lastName;
}

std::string Client::getPersonalID() {
    return this->personalID;
}

void Client::setFirstName(std::string firstName) {
    if (firstName != "") {
        this->firstName = firstName;
    }
}

void Client::setLastName(std::string lastName) {
    if (lastName != "") {
        this->lastName = lastName;
    }
}