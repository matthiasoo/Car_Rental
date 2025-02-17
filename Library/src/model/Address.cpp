#include "Address.h"

Address::Address(const std::string &city, const std::string &street, const std::string &number) :
    city(city),
    street(street),
    number(number) {}

Address::~Address() {}

std::string Address::getAddressInfo() const {
    return "ADDRESS: " + this->city + " " + this->street + " " + this->number;
}

const std::string & Address::getCity() const {
    return this->city;
}

const std::string & Address::getStreet() const {
    return this->street;
}

const std::string & Address::getNumber() const {
    return this->number;
}

// void Address::setCity(std::string city) {
//     if (city != "") {
//         this->city = city;
//     }
// }
//
// void Address::setStreet(std::string street) {
//     if (street != "") {
//         this->street = street;
//     }
// }
//
// void Address::setNumber(std::string number) {
//     if (number != "") {
//         this->number = number;
//     }
// }