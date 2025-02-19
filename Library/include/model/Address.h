#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include "typedefs.h"

class Address {
private:
    std::string city;
    std::string street;
    std::string number;

public:
    Address(const std::string &city, const std::string &street, const std::string &number);
    ~Address();

    // getters
    std::string getAddressInfo() const;
    const std::string &getCity() const;
    const std::string &getStreet() const;
    const std::string &getNumber() const;
};



#endif //ADDRESS_H
